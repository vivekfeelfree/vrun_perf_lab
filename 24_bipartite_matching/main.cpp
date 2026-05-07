/**
 * EXPERIMENT: Bipartite Matching (Hopcroft-Karp)
 * 
 * GOAL: Compare Hopcroft-Karp performance against standard max flow 
 * for bipartite matching problems.
 * 
 * Complexity: O(E sqrt(V)).
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1e9;

class HopcroftKarp {
    int n, m;
    std::vector<std::vector<int>> adj;
    std::vector<int> matchL, matchR, dist;

public:
    HopcroftKarp(int n, int m) : n(n), m(m), adj(n + 1), matchL(n + 1, 0), matchR(m + 1, 0), dist(n + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        std::queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (matchL[i] == 0) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = INF;
            }
        }
        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[matchR[v]] == INF) {
                        dist[matchR[v]] = dist[u] + 1;
                        q.push(matchR[v]);
                    }
                }
            }
        }
        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                if (dist[matchR[v]] == dist[u] + 1) {
                    if (dfs(matchR[v])) {
                        matchR[v] = u;
                        matchL[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int matching() {
        int result = 0;
        while (bfs()) {
            for (int i = 1; i <= n; ++i) {
                if (matchL[i] == 0 && dfs(i)) {
                    result++;
                }
            }
        }
        return result;
    }

    size_t memory_usage() const {
        size_t total = sizeof(*this);
        for (const auto& v : adj) total += v.size() * sizeof(int) + sizeof(std::vector<int>);
        total += matchL.size() * sizeof(int) + matchR.size() * sizeof(int) + dist.size() * sizeof(int);
        return total;
    }
};

int main() {
    int N = 5000; // Left side nodes
    int M = 5000; // Right side nodes
    std::cout << "--- Bipartite Matching Laboratory (" << N << "x" << M << ") ---" << std::endl;

    HopcroftKarp hk(N, M);
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < 5; ++j) {
            hk.add_edge(i, (rand() % M) + 1);
        }
    }

    lab::print_qor("Bipartite Graph", hk.memory_usage());

    int matches = 0;
    {
        lab::Benchmark b("Hopcroft-Karp Matching");
        matches = hk.matching();
    }

    lab::print_qor("Final Result", hk.memory_usage(), (size_t)matches);
    std::cout << "[METRICS] Max Matching: " << matches << std::endl;

    return 0;
}
