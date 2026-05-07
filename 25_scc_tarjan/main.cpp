/**
 * EXPERIMENT: Strongly Connected Components (Tarjan's Algorithm)
 * 
 * GOAL: Measure the performance of Tarjan's algorithm for SCC detection, 
 * a core component of logic synthesis and dependency analysis.
 * 
 * Complexity: O(V + E).
 */

#include "../include/harness.hpp"
#include <vector>
#include <stack>
#include <algorithm>

class TarjanSCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> disc, low;
    std::vector<bool> on_stack;
    std::stack<int> st;
    int timer;
    int scc_count;

public:
    TarjanSCC(int n) : n(n), adj(n), disc(n, -1), low(n, -1), on_stack(n, false), timer(0), scc_count(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void find_sccs(int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                find_sccs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            scc_count++;
            while (true) {
                int v = st.top();
                st.pop();
                on_stack[v] = false;
                if (u == v) break;
            }
        }
    }

    int run() {
        for (int i = 0; i < n; ++i) {
            if (disc[i] == -1) find_sccs(i);
        }
        return scc_count;
    }

    size_t memory_usage() const {
        size_t total = sizeof(*this);
        for (const auto& v : adj) total += v.size() * sizeof(int) + sizeof(std::vector<int>);
        total += disc.size() * sizeof(int) * 2 + on_stack.size() * sizeof(bool);
        return total;
    }
};

int main() {
    int N = 10000;
    std::cout << "--- Tarjan's SCC Laboratory (" << N << " nodes) ---" << std::endl;

    TarjanSCC tarjan(N);
    // Random graph with some locality to form SCCs
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            tarjan.add_edge(i, (i + rand() % 100) % N);
        }
    }

    lab::print_qor("Initial Graph", tarjan.memory_usage());

    int count = 0;
    {
        lab::Benchmark b("Tarjan SCC Detection");
        count = tarjan.run();
    }

    lab::print_qor("Final Result", tarjan.memory_usage(), (size_t)count);
    std::cout << "[METRICS] SCCs Found: " << count << std::endl;

    return 0;
}
