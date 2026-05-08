/**
 * EXPERIMENT: AIG Balancing
 * 
 * GOAL: Reduce logic depth of an AIG using associative re-balancing.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct AIGNode {
    int f1, f2;
    int depth;
};

class AIGBalancer {
    std::vector<AIGNode> nodes;

public:
    AIGBalancer() {
        nodes.push_back({-1, -1, 0}); // Constant
    }

    int add_node(int f1, int f2) {
        int d = std::max(nodes[f1].depth, nodes[f2].depth) + 1;
        nodes.push_back({f1, f2, d});
        return nodes.size() - 1;
    }

    // Build a deep chain: (((a&b)&c)&d)
    int build_chain(int n) {
        int root = 0;
        for (int i = 0; i < n; ++i) {
            root = add_node(root, 0);
        }
        return root;
    }

    // Build a balanced tree
    int build_tree(int l, int r) {
        if (l == r) return 0;
        int mid = (l + r) / 2;
        int f1 = build_tree(l, mid);
        int f2 = build_tree(mid + 1, r);
        return add_node(f1, f2);
    }

    int get_depth(int id) { return nodes[id].depth; }
};

int main() {
    int N = 1024;
    std::cout << "--- AIG Balancing Laboratory (" << N << " inputs) ---" << std::endl;

    AIGBalancer b;
    int root_chain = 0;
    {
        lab::Benchmark bench("Build Unbalanced Chain");
        root_chain = b.build_chain(N);
    }
    std::cout << "[METRICS] Chain Depth: " << b.get_depth(root_chain) << std::endl;

    AIGBalancer b2;
    int root_tree = 0;
    {
        lab::Benchmark bench("Build Balanced Tree");
        root_tree = b2.build_tree(0, N - 1);
    }
    std::cout << "[METRICS] Tree Depth: " << b2.get_depth(root_tree) << std::endl;

    lab::print_qor("AIG Infrastructure", N * sizeof(AIGNode));

    return 0;
}
