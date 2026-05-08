/**
 * EXPERIMENT: Minimum Vertex Cover (2-Approximation)
 * 
 * GOAL: Implement the 2-approximation greedy algorithm for 
 * minimum vertex cover and measure its result quality.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Edge { int u, v; };

class VertexCoverApprox {
    int n;
    std::vector<Edge> edges;

public:
    VertexCoverApprox(int nodes) : n(nodes) {}
    void add_edge(int u, int v) { edges.push_back({u, v}); }

    int solve() {
        std::vector<bool> covered(n, false);
        std::vector<bool> edge_covered(edges.size(), false);
        int cover_size = 0;

        for (int i = 0; i < (int)edges.size(); ++i) {
            if (!covered[edges[i].u] && !covered[edges[i].v]) {
                covered[edges[i].u] = true;
                covered[edges[i].v] = true;
                cover_size += 2;
            }
        }
        return cover_size;
    }

    size_t memory_usage() const { return edges.size() * sizeof(Edge); }
};

int main() {
    int N = 1000, E = 5000;
    std::cout << "--- Vertex Cover (2-Approx) Laboratory (" << N << " nodes) ---" << std::endl;

    VertexCoverApprox vca(N);
    for (int i = 0; i < E; ++i) vca.add_edge(rand() % N, rand() % N);

    lab::print_qor("Initial Graph", vca.memory_usage());

    int cover = 0;
    {
        lab::Benchmark b("Greedy 2-Approximation VC");
        cover = vca.solve();
    }

    std::cout << "[METRICS] Approximation Cover Size: " << cover << std::endl;
    lab::print_qor("Final Result", 0, cover);

    return 0;
}
