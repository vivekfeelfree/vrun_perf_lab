/**
 * EXPERIMENT: FPGA LUT Mapping
 * 
 * GOAL: Implement a heuristic for mapping a logic graph into K-input 
 * Look-Up Tables (LUTs), minimizing total LUT count and depth.
 */

#include "../include/harness.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include <map>

struct Node {
    int id;
    int fanin[2];
    int depth;
    bool is_pi;
};

class LUTMapper {
    int K;
    std::vector<Node> nodes;
    int pi_count;

public:
    LUTMapper(int k, int pi) : K(k), pi_count(pi) {
        for (int i = 0; i < pi; ++i) {
            nodes.push_back({i, {-1, -1}, 0, true});
        }
    }

    void add_gate(int id, int f1, int f2) {
        int d = std::max(nodes[f1].depth, nodes[f2].depth) + 1;
        nodes.push_back({id, {f1, f2}, d, false});
    }

    // A very simple greedy cut-finding heuristic for K-LUT mapping
    int compute_lut_count() {
        int lut_count = 0;
        std::vector<bool> covered(nodes.size(), false);
        
        // Traverse in reverse topological order (from POs)
        // For this experiment, we'll just treat the last N nodes as POs
        for (int i = (int)nodes.size() - 1; i >= pi_count; --i) {
            if (covered[i]) continue;
            
            // "Map" this node to a LUT
            lut_count++;
            std::set<int> leaf_set;
            find_cut(i, leaf_set);
            
            for (int leaf : leaf_set) {
                if (leaf >= pi_count) {
                    // This leaf is an internal node that needs its own LUT
                }
            }
            covered[i] = true;
        }
        return lut_count;
    }

    void find_cut(int root, std::set<int>& leaves) {
        if (nodes[root].is_pi || leaves.size() >= (size_t)K) {
            leaves.insert(root);
            return;
        }
        
        // Greedy expansion: expand the fanin with larger depth
        int f1 = nodes[root].fanin[0];
        int f2 = nodes[root].fanin[1];
        
        if (nodes[f1].depth >= nodes[f2].depth) {
            find_cut(f1, leaves);
            if (leaves.size() < (size_t)K) find_cut(f2, leaves);
            else leaves.insert(f2);
        } else {
            find_cut(f2, leaves);
            if (leaves.size() < (size_t)K) find_cut(f1, leaves);
            else leaves.insert(f1);
        }
    }

    size_t memory_usage() const {
        return nodes.size() * sizeof(Node) + sizeof(*this);
    }
};

int main() {
    int K = 4;
    int PI = 100;
    int GATES = 1000;
    std::cout << "--- FPGA LUT Mapping Laboratory (K=" << K << ") ---" << std::endl;

    LUTMapper mapper(K, PI);
    for (int i = PI; i < PI + GATES; ++i) {
        mapper.add_gate(i, rand() % i, rand() % i);
    }

    lab::print_qor("Initial Netlist", mapper.memory_usage(), GATES);

    int luts = 0;
    {
        lab::Benchmark b("Greedy LUT Mapping");
        luts = mapper.compute_lut_count();
    }

    lab::print_qor("Mapped Result", mapper.memory_usage(), (size_t)luts);
    std::cout << "[METRICS] Total LUTs: " << luts << " | Reduction: " << (float)(GATES - luts) / GATES * 100 << "%" << std::endl;

    return 0;
}
