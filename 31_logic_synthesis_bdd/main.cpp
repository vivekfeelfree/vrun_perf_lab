/**
 * EXPERIMENT: Binary Decision Diagrams (BDDs) and Structural Hashing
 * 
 * GOAL: Demonstrate canonicality in boolean functions through 
 * a Unique Table and memoization.
 */

#include "../include/harness.hpp"
#include <unordered_map>
#include <tuple>

/**
 * A BDD Node representing a Shannon decomposition:
 * f = var ? high : low
 */
struct BDDNode {
    int var;        // Variable index
    int low, high;  // Indices of child nodes

    bool operator==(const BDDNode& other) const {
        return var == other.var && low == other.low && high == other.high;
    }
};

/**
 * Custom Hash for BDDNode to use in Unique Table
 */
struct BDDNodeHash {
    size_t operator()(const BDDNode& n) const {
        return std::hash<int>{}(n.var) ^ (std::hash<int>{}(n.low) << 1) ^ (std::hash<int>{}(n.high) << 2);
    }
};

class BDDManager {
    std::vector<BDDNode> nodes;
    // The Unique Table: Ensures no duplicate nodes
    std::unordered_map<BDDNode, int, BDDNodeHash> unique_table;

public:
    static constexpr int BDD_FALSE = 0;
    static constexpr int BDD_TRUE = 1;

    BDDManager() {
        // Constant nodes
        nodes.push_back({-1, -1, -1}); // 0: False
        nodes.push_back({-1, -1, -1}); // 1: True
    }

    int create_node(int var, int low, int high) {
        if (low == high) return low; // Redundant node optimization

        BDDNode n{var, low, high};
        auto it = unique_table.find(n);
        if (it != unique_table.end()) return it->second;

        int id = nodes.size();
        nodes.push_back(n);
        unique_table[n] = id;
        return id;
    }

    // A simple 'AND' operation for BDDs
    // In a real manager, this would use a Computed Table for memoization
    int bdd_and(int f, int g) {
        if (f == BDD_FALSE || g == BDD_FALSE) return BDD_FALSE;
        if (f == BDD_TRUE) return g;
        if (g == BDD_TRUE) return f;
        if (f == g) return f;

        // Simplified recursive step for demonstration
        // Normally we'd pick the top variable and recurse
        return BDD_FALSE; // Placeholder
    }

    size_t num_nodes() const { return nodes.size(); }
};

int main() {
    std::cout << "--- BDD Laboratory (Structural Hashing) ---" << std::endl;

    BDDManager mgr;

    // Create a function: f = (x0 AND x1)
    // Variable ordering: x0 is top
    int x1_true = mgr.create_node(1, BDDManager::BDD_FALSE, BDDManager::BDD_TRUE);
    int f1 = mgr.create_node(0, BDDManager::BDD_FALSE, x1_true);

    // Create the SAME function again using different code paths
    int x1_true_again = mgr.create_node(1, BDDManager::BDD_FALSE, BDDManager::BDD_TRUE);
    int f2 = mgr.create_node(0, BDDManager::BDD_FALSE, x1_true_again);

    std::cout << "Node index for f1: " << f1 << std::endl;
    std::cout << "Node index for f2: " << f2 << std::endl;

    if (f1 == f2) {
        std::cout << "SUCCESS: Structural Hashing detected identical logic!" << std::endl;
    } else {
        std::cout << "FAILURE: Nodes are different." << std::endl;
    }

    size_t est_mem = mgr.num_nodes() * sizeof(BDDNode) + (mgr.num_nodes() * (sizeof(BDDNode) + sizeof(int)) * 1.5); // Estimate for unordered_map
    lab::print_qor("BDD Manager", est_mem, mgr.num_nodes());

    std::cout << "Total unique nodes created: " << mgr.num_nodes() << " (Expected: 3 - x1, f1, and constants)" << std::endl;

    return 0;
}
