/**
 * EXPERIMENT: Maximum Clique (Branch and Bound)
 * 
 * GOAL: Find the largest fully connected subgraph (clique) using 
 * a branch and bound search.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

class CliqueSolver {
    int n;
    std::vector<std::vector<bool>> adj;
    int max_clique_size = 0;

public:
    CliqueSolver(int nodes) : n(nodes), adj(nodes, std::vector<bool>(nodes, false)) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        adj[u][v] = adj[v][u] = true;
    }

    bool is_clique(const std::vector<int>& nodes) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                if (!adj[nodes[i]][nodes[j]]) return false;
            }
        }
        return true;
    }

    void solve(std::vector<int> current, int start_node) {
        if (current.size() > (size_t)max_clique_size) {
            max_clique_size = current.size();
        }

        for (int i = start_node; i < n; ++i) {
            if (current.size() + (n - i) <= (size_t)max_clique_size) return; // Pruning

            bool can_add = true;
            for (int node : current) {
                if (!adj[i][node]) {
                    can_add = false;
                    break;
                }
            }

            if (can_add) {
                current.push_back(i);
                solve(current, i + 1);
                current.pop_back();
            }
        }
    }

    int get_max_clique() { return max_clique_size; }
    size_t memory_usage() const { return n * n * sizeof(bool); }
};

int main() {
    int N = 40;
    std::cout << "--- Maximum Clique (Branch & Bound) Laboratory (" << N << " nodes) ---" << std::endl;

    CliqueSolver solver(N);
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (rand() % 10 < 3) solver.add_edge(i, j); // Sparse graph
        }
    }

    lab::print_qor("Adjacency Matrix", solver.memory_usage());

    {
        lab::Benchmark b("Max Clique Search");
        solver.solve({}, 0);
    }

    std::cout << "[METRICS] Maximum Clique Size: " << solver.get_max_clique() << std::endl;
    lab::print_qor("Final Result", 0, solver.get_max_clique());

    return 0;
}
