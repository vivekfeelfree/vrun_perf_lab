/**
 * EXPERIMENT: Observability Don't Cares (ODC)
 * 
 * GOAL: Identify logic nodes that are "don't cares" because their 
 * value doesn't propagate to any primary output.
 */

#include "../include/harness.hpp"
#include <vector>
#include <bitset>

class ODCOptimizer {
    int n_pi;
    struct Node { int f1, f2; };
    std::vector<Node> nodes;

public:
    ODCOptimizer(int pi) : n_pi(pi) {}

    void add_gate(int f1, int f2) { nodes.push_back({f1, f2}); }

    int find_odcs(int patterns) {
        int odc_count = 0;
        int n_nodes = nodes.size();
        
        // Simulating 64 patterns at once using bitsets
        std::vector<uint64_t> values(n_pi + n_nodes);
        for (int i = 0; i < n_pi; ++i) values[i] = rand();

        for (int i = 0; i < n_nodes; ++i) {
            values[n_pi + i] = values[nodes[i].f1] & values[nodes[i].f2];
        }

        // Observability analysis: Flip a node's value and see if the output changes
        uint64_t output_orig = values.back();
        
        for (int i = 0; i < n_nodes - 1; ++i) {
            // Re-simulate partially
            std::vector<uint64_t> temp_values = values;
            temp_values[n_pi + i] = ~values[n_pi + i]; // Flip
            
            for (int j = i + 1; j < n_nodes; ++j) {
                temp_values[n_pi + j] = temp_values[nodes[j].f1] & temp_values[nodes[j].f2];
            }
            
            if (temp_values.back() == output_orig) {
                odc_count++; // Output didn't change for any of the 64 patterns
            }
        }
        return odc_count;
    }

    size_t memory_usage() const {
        return nodes.size() * sizeof(Node) + sizeof(*this);
    }
};

int main() {
    int PI = 10;
    int GATES = 200;
    std::cout << "--- ODC Optimization Laboratory ---" << std::endl;

    ODCOptimizer opt(PI);
    for (int i = 0; i < GATES; ++i) {
        opt.add_gate(rand() % (PI + i), rand() % (PI + i));
    }

    lab::print_qor("Initial Design", opt.memory_usage());

    int odcs = 0;
    {
        lab::Benchmark b("ODC Identification (64 patterns)");
        odcs = opt.find_odcs(64);
    }

    std::cout << "[METRICS] Potential ODC Nodes: " << odcs << std::endl;

    return 0;
}
