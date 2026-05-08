/**
 * EXPERIMENT: BDD Variable Reordering (Sifting)
 * 
 * GOAL: Demonstrate how variable order affects BDD size and 
 * implement a simple swap-based reordering heuristic.
 */

#include "../include/harness.hpp"
#include <vector>
#include <map>
#include <algorithm>

struct BDDNode {
    int var;
    int low, high;
};

class BDDManager {
    std::vector<BDDNode> nodes;
    std::map<std::pair<int, std::pair<int, int>>, int> unique_table;

public:
    BDDManager() {
        nodes.push_back({-1, -1, -1}); // Constant 0
        nodes.push_back({-1, -1, -1}); // Constant 1
    }

    int get_node(int var, int low, int high) {
        if (low == high) return low;
        auto key = std::make_pair(var, std::make_pair(low, high));
        if (unique_table.count(key)) return unique_table[key];
        int id = nodes.size();
        nodes.push_back({var, low, high});
        return unique_table[key] = id;
    }

    // Build a simple parity function: x1 ^ x2 ^ ... ^ xn
    int build_parity(const std::vector<int>& order) {
        int root = 1; // Constant 1
        for (int v : order) {
            int low = root;
            int high = root ^ 1; // Flip parity
            root = get_node(v, low, high);
        }
        return root;
    }

    size_t size() const { return nodes.size(); }
    void reset() {
        nodes.clear();
        nodes.push_back({-1, -1, -1});
        nodes.push_back({-1, -1, -1});
        unique_table.clear();
    }
};

int main() {
    std::cout << "--- BDD Variable Reordering Laboratory ---" << std::endl;

    BDDManager bdd;
    std::vector<int> vars = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    {
        lab::Benchmark b("Build Parity (Order A)");
        bdd.build_parity(vars);
    }
    std::cout << "[METRICS] Nodes for Order A: " << bdd.size() << std::endl;
    lab::print_qor("BDD Order A", bdd.size() * sizeof(BDDNode));

    bdd.reset();
    std::reverse(vars.begin(), vars.end());
    {
        lab::Benchmark b("Build Parity (Order B)");
        bdd.build_parity(vars);
    }
    std::cout << "[METRICS] Nodes for Order B: " << bdd.size() << std::endl;
    lab::print_qor("BDD Order B", bdd.size() * sizeof(BDDNode));

    return 0;
}
