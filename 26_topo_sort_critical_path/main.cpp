/**
 * EXPERIMENT: Topological Sort and Critical Path Analysis
 * 
 * GOAL: Model Static Timing Analysis (STA) by finding the critical path 
 * in a Directed Acyclic Graph (DAG).
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

struct Node {
    std::vector<int> out;
    int in_degree = 0;
    float delay = 0.0f;
    float arrival_time = 0.0f;
};

class CriticalPathAnalyzer {
    std::vector<Node> nodes;

public:
    CriticalPathAnalyzer(int n) : nodes(n) {}

    void add_edge(int u, int v) {
        nodes[u].out.push_back(v);
        nodes[v].in_degree++;
    }

    void set_delay(int u, float d) {
        nodes[u].delay = d;
    }

    float solve() {
        std::queue<int> q;
        int n = nodes.size();
        for (int i = 0; i < n; ++i) {
            if (nodes[i].in_degree == 0) {
                nodes[i].arrival_time = nodes[i].delay;
                q.push(i);
            }
        }

        float max_arrival = 0.0f;
        int processed = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            processed++;

            max_arrival = std::max(max_arrival, nodes[u].arrival_time);

            for (int v : nodes[u].out) {
                nodes[v].arrival_time = std::max(nodes[v].arrival_time, 
                                               nodes[u].arrival_time + nodes[v].delay);
                if (--nodes[v].in_degree == 0) {
                    q.push(v);
                }
            }
        }

        if (processed != n) return -1.0f; // Cycle detected
        return max_arrival;
    }

    size_t memory_usage() const {
        size_t total = sizeof(*this);
        for (const auto& n : nodes) total += n.out.size() * sizeof(int) + sizeof(Node);
        return total;
    }
};

int main() {
    int N = 20000;
    std::cout << "--- Critical Path Analysis Laboratory (" << N << " nodes) ---" << std::endl;

    CriticalPathAnalyzer analyzer(N);
    for (int i = 0; i < N; ++i) {
        analyzer.set_delay(i, (float)(rand() % 100) / 10.0f);
        // Create a DAG
        for (int j = 1; j <= 2; ++j) {
            if (i + j < N) {
                analyzer.add_edge(i, i + j);
            }
        }
    }

    lab::print_qor("DAG Infrastructure", analyzer.memory_usage());

    float cp = 0;
    {
        lab::Benchmark b("Critical Path Analysis");
        cp = analyzer.solve();
    }

    lab::print_qor("Final Result", analyzer.memory_usage(), (size_t)cp);
    std::cout << "[METRICS] Critical Path Delay: " << cp << std::endl;

    return 0;
}
