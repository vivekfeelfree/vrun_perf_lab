/**
 * EXPERIMENT: Min-Cost Max-Flow (Successive Shortest Path)
 * 
 * GOAL: Implement and measure min-cost max-flow, a critical algorithm 
 * for resource allocation and pin assignment in EDA.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

const long long INF = 1e18;

struct Edge {
    int to, rev;
    long long cap, flow, cost;
};

class MCMF {
    std::vector<std::vector<Edge>> adj;
    std::vector<long long> dist;
    std::vector<int> parent_edge;
    std::vector<int> parent_node;

public:
    MCMF(int n) : adj(n), dist(n), parent_edge(n), parent_node(n) {}

    void add_edge(int from, int to, long long cap, long long cost) {
        adj[from].push_back({to, (int)adj[to].size(), cap, 0, cost});
        adj[to].push_back({from, (int)adj[from].size() - 1, 0, 0, -cost});
    }

    bool spfa(int s, int t, long long& flow, long long& cost) {
        std::fill(dist.begin(), dist.end(), INF);
        std::vector<bool> in_queue(adj.size(), false);
        std::queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int i = 0; i < (int)adj[u].size(); ++i) {
                Edge& e = adj[u][i];
                if (e.cap - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent_node[e.to] = u;
                    parent_edge[e.to] = i;
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
        }

        if (dist[t] == INF) return false;

        long long push = INF;
        int curr = t;
        while (curr != s) {
            int prev = parent_node[curr];
            int idx = parent_edge[curr];
            push = std::min(push, adj[prev][idx].cap - adj[prev][idx].flow);
            curr = prev;
        }

        flow += push;
        curr = t;
        while (curr != s) {
            int prev = parent_node[curr];
            int idx = parent_edge[curr];
            adj[prev][idx].flow += push;
            int rev_idx = adj[prev][idx].rev;
            adj[curr][rev_idx].flow -= push;
            cost += push * adj[prev][idx].cost;
            curr = prev;
        }

        return true;
    }

    std::pair<long long, long long> solve(int s, int t) {
        long long flow = 0, cost = 0;
        while (spfa(s, t, flow, cost));
        return {flow, cost};
    }

    size_t memory_usage() const {
        size_t total = sizeof(*this);
        for (const auto& v : adj) total += v.size() * sizeof(Edge) + sizeof(std::vector<Edge>);
        total += dist.size() * sizeof(long long) + parent_edge.size() * sizeof(int) + parent_node.size() * sizeof(int);
        return total;
    }
};

int main() {
    int N = 200;
    int S = 0, T = N - 1;
    std::cout << "--- Min-Cost Max-Flow Laboratory (" << N << " nodes) ---" << std::endl;

    MCMF mcmf(N);
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 1; j <= 3; ++j) {
            if (i + j < N) {
                mcmf.add_edge(i, i + j, rand() % 10 + 1, rand() % 50 + 1);
            }
        }
    }

    lab::print_qor("Network Setup", mcmf.memory_usage());

    std::pair<long long, long long> result;
    {
        lab::Benchmark b("MCMF Successive Shortest Path");
        result = mcmf.solve(S, T);
    }

    lab::print_qor("Final MCMF", mcmf.memory_usage(), (size_t)result.second);
    std::cout << "[METRICS] Max Flow: " << result.first << " | Min Cost: " << result.second << std::endl;

    return 0;
}
