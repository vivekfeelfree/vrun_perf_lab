/**
 * EXPERIMENT: Maximum Flow (Dinic's Algorithm)
 * 
 * GOAL: Measure the performance of Dinic's algorithm for finding 
 * the maximum flow in a network.
 * 
 * Complexity: O(V^2 E), but O(E sqrt(V)) for unit networks.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

struct Edge {
    int to, rev;
    long long cap, flow;
};

class Dinic {
    std::vector<std::vector<Edge>> adj;
    std::vector<int> level;
    std::vector<int> ptr;

public:
    Dinic(int n) : adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, long long cap) {
        adj[from].push_back({to, (int)adj[to].size(), cap, 0});
        adj[to].push_back({from, (int)adj[from].size() - 1, 0, 0});
    }

    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, int t, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            long long tr_pushed = dfs(tr, t, std::min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0) continue;
            edge.flow += tr_pushed;
            adj[tr][edge.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, 1e18)) {
                flow += pushed;
            }
        }
        return flow;
    }

    size_t memory_usage() const {
        size_t total = sizeof(*this);
        for (const auto& v : adj) total += v.size() * sizeof(Edge) + sizeof(std::vector<Edge>);
        total += level.size() * sizeof(int) + ptr.size() * sizeof(int);
        return total;
    }
};

int main() {
    int N = 500;
    int S = 0, T = N - 1;
    std::cout << "--- Dinic Max Flow Laboratory (" << N << " nodes) ---" << std::endl;

    Dinic dinic(N);
    // Create a layered-ish graph
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if (i + j < N) {
                dinic.add_edge(i, i + j, rand() % 100 + 1);
            }
        }
    }

    lab::print_qor("Initial Network", dinic.memory_usage());

    long long flow = 0;
    {
        lab::Benchmark b("Dinic Max Flow");
        flow = dinic.max_flow(S, T);
    }

    lab::print_qor("Final Result", dinic.memory_usage(), (size_t)flow);
    std::cout << "[METRICS] Max Flow: " << flow << std::endl;

    return 0;
}
