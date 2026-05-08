/**
 * EXPERIMENT: Boolean Rewriting (AIG Optimization)
 * 
 * GOAL: Demonstrate local sub-graph rewriting to reduce AIG node count.
 */

#include "../include/harness.hpp"
#include <vector>
#include <unordered_map>

struct AIGNode {
    int f0, f1; // Fanins (id << 1 | complement_bit)
};

class AIGRewriter {
    std::vector<AIGNode> nodes;
    std::unordered_map<long long, int> strash;

public:
    AIGRewriter() {
        nodes.push_back({0, 0}); // Constant 0
    }

    int add_node(int f0, int f1) {
        if (f0 > f1) std::swap(f0, f1);
        if (f0 == f1) return f0;
        if (f0 == 0) return 0;
        if (f0 == 1) return f1;
        
        long long key = ((long long)f0 << 32) | f1;
        if (strash.count(key)) return strash[key];
        
        int id = nodes.size();
        nodes.push_back({f0, f1});
        return strash[key] = (id << 1);
    }

    // A simple rewriting rule: (A & B) & A -> A & B
    int rewrite_associative(int f0, int f1) {
        int id0 = f0 >> 1;
        int id1 = f1 >> 1;
        
        if (id0 != 0 && (nodes[id0].f0 >> 1 == id1 || nodes[id0].f1 >> 1 == id1)) {
            return f0; // Simplified
        }
        if (id1 != 0 && (nodes[id1].f0 >> 1 == id0 || nodes[id1].f1 >> 1 == id0)) {
            return f1; // Simplified
        }
        
        return add_node(f0, f1);
    }

    size_t size() const { return nodes.size(); }
};

int main() {
    std::cout << "--- Boolean Rewriting Laboratory ---" << std::endl;

    AIGRewriter aig;
    int pi1 = 2, pi2 = 4, pi3 = 6;

    {
        lab::Benchmark b("Structural Hashing (Strashing)");
        for (int i = 0; i < 1000; ++i) {
            aig.add_node(pi1, pi2);
        }
    }
    std::cout << "[METRICS] Nodes after strashing: " << aig.size() << std::endl;

    {
        lab::Benchmark b("Local Rewriting Rules");
        int n1 = aig.add_node(pi1, pi2);
        for (int i = 0; i < 1000; ++i) {
            aig.rewrite_associative(n1, pi1);
        }
    }
    std::cout << "[METRICS] Nodes after rewriting: " << aig.size() << std::endl;

    lab::print_qor("AIG Footprint", aig.size() * sizeof(AIGNode));

    return 0;
}
