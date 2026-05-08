/**
 * EXPERIMENT: Hamiltonian Path (Backtracking)
 * 
 * GOAL: Find a path that visits every vertex exactly once using 
 * an exhaustive backtracking search.
 */

#include "../include/harness.hpp"
#include <vector>
#include <iostream>

class HamiltonianSolver {
    int n;
    std::vector<std::vector<bool>> adj;
    std::vector<int> path;

public:
    HamiltonianSolver(int nodes) : n(nodes), adj(nodes, std::vector<bool>(nodes, false)) {}

    void add_edge(int u, int v) { adj[u][v] = adj[v][u] = true; }

    bool solve(int pos) {
        if (pos == n) return true;

        for (int v = 0; v < n; ++v) {
            bool already_in_path = false;
            for (int i = 0; i < pos; ++i) if (path[i] == v) already_in_path = true;

            if (!already_in_path && adj[path[pos - 1]][v]) {
                path[pos] = v;
                if (solve(pos + 1)) return true;
                // Backtrack (path[pos] will be overwritten)
            }
        }
        return false;
    }

    bool find_path() {
        path.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            path[0] = i;
            if (solve(1)) return true;
        }
        return false;
    }
};

int main() {
    int N = 15; // Small N due to exponential complexity
    std::cout << "--- Hamiltonian Path Laboratory (N=" << N << ") ---" << std::endl;

    HamiltonianSolver solver(N);
    // Create a dense-ish graph to ensure a path exists with high probability
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (rand() % 10 < 6) solver.add_edge(i, j);
        }
    }

    bool found = false;
    {
        lab::Benchmark b("Hamiltonian Path Backtracking");
        found = solver.find_path();
    }

    std::cout << "[METRICS] Path Found: " << (found ? "YES" : "NO") << std::endl;
    lab::print_qor("Search Footprint", N * N * sizeof(bool));

    return 0;
}
