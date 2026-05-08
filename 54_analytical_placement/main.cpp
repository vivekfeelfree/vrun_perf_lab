/**
 * EXPERIMENT: Force-Directed Analytical Placement
 * 
 * GOAL: Model nets as springs and use a force-directed heuristic 
 * to find node positions that minimize total wirelength.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

struct Node {
    float x, y;
    float fx, fy;
};

struct Edge {
    int u, v;
};

class ForceDirectedPlacer {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    float K; // Spring constant

public:
    ForceDirectedPlacer(int n, float k) : nodes(n), K(k) {
        for (int i = 0; i < n; ++i) {
            nodes[i] = {(float)(rand() % 100), (float)(rand() % 100), 0, 0};
        }
    }

    void add_edge(int u, int v) { edges.push_back({u, v}); }

    void step(float delta) {
        // Reset forces
        for (auto& n : nodes) n.fx = n.fy = 0;

        // Attractive forces (Springs)
        for (const auto& e : edges) {
            float dx = nodes[e.v].x - nodes[e.u].x;
            float dy = nodes[e.v].y - nodes[e.u].y;
            float dist = std::max(0.1f, std::sqrt(dx * dx + dy * dy));
            float force = K * (dist);
            nodes[e.u].fx += force * (dx / dist);
            nodes[e.u].fy += force * (dy / dist);
            nodes[e.v].fx -= force * (dx / dist);
            nodes[e.v].fy -= force * (dy / dist);
        }

        // Apply forces
        for (auto& n : nodes) {
            n.x += n.fx * delta;
            n.y += n.fy * delta;
        }
    }

    float compute_hpwl() {
        float total = 0;
        for (const auto& e : edges) {
            total += std::abs(nodes[e.u].x - nodes[e.v].x) + std::abs(nodes[e.u].y - nodes[e.v].y);
        }
        return total;
    }

    size_t memory_usage() const {
        return nodes.size() * sizeof(Node) + edges.size() * sizeof(Edge);
    }
};

int main() {
    int N = 1000, E = 2000;
    std::cout << "--- Force-Directed Placement Laboratory (" << N << " nodes) ---" << std::endl;

    ForceDirectedPlacer placer(N, 0.01f);
    for (int i = 0; i < E; ++i) placer.add_edge(rand() % N, rand() % N);

    lab::print_qor("Initial Netlist", placer.memory_usage());
    std::cout << "[METRICS] Initial HPWL: " << placer.compute_hpwl() << std::endl;

    {
        lab::Benchmark b("Force-Directed Optimization (100 steps)");
        for (int i = 0; i < 100; ++i) placer.step(0.1f);
    }

    std::cout << "[METRICS] Final HPWL: " << placer.compute_hpwl() << std::endl;
    lab::print_qor("Final Result", 0, (size_t)placer.compute_hpwl());

    return 0;
}
