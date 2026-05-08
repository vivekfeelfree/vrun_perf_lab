/**
 * EXPERIMENT: Longest Path in a DAG
 * 
 * GOAL: Find the longest path in a Directed Acyclic Graph (DAG) 
 * using topological sorting.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

class LongestPathSolver {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> in_degree;

public:
    LongestPathSolver(int nodes) : n(nodes), adj(nodes), in_degree(nodes, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        in_degree[v]++;
    }

    int solve() {
        std::vector<int> dist(n, -1e9);
        std::queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
                dist[i] = 0;
            }
        }

        int max_dist = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] < dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                }
                if (--in_degree[v] == 0) q.push(v);
            }
            max_dist = std::max(max_dist, dist[u]);
        }
        return max_dist;
    }

    size_t memory_usage() const { return n * sizeof(std::vector<int>) + n * sizeof(int); }
};

int main() {
    int N = 1000;
    std::cout << "--- Longest Path in DAG Laboratory (" << N << " nodes) ---" << std::endl;

    LongestPathSolver solver(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= 2; ++j) {
            if (i + j < N) solver.add_edge(i, i + j);
        }
    }

    lab::print_qor("DAG Database", solver.memory_usage());

    int lp = 0;
    {
        lab::Benchmark b("Longest Path Computation");
        lp = solver.solve();
    }

    std::cout << "[METRICS] Longest Path Distance: " << lp << std::endl;
    lab::print_qor("Final Result", 0, lp);

    return 0;
}
