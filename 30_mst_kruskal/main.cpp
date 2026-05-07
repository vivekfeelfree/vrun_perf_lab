/**
 * EXPERIMENT: Minimum Spanning Tree (Kruskal's Algorithm)
 * 
 * GOAL: Use DSU to implement Kruskal's algorithm and measure its 
 * performance on a large graph.
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const { return weight < other.weight; }
};

class DSU {
    std::vector<int> parent;
public:
    DSU(int n) : parent(n) { std::iota(parent.begin(), parent.end(), 0); }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

class Kruskal {
    int n;
    std::vector<Edge> edges;
public:
    Kruskal(int n) : n(n) {}
    void add_edge(int u, int v, int w) { edges.push_back({u, v, w}); }

    long long solve() {
        std::sort(edges.begin(), edges.end());
        DSU dsu(n);
        long long mst_weight = 0;
        int edges_count = 0;
        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                mst_weight += e.weight;
                edges_count++;
            }
        }
        return mst_weight;
    }

    size_t memory_usage() const {
        return edges.size() * sizeof(Edge) + sizeof(*this);
    }
};

int main() {
    int N = 50000;
    std::cout << "--- Kruskal's MST Laboratory (" << N << " nodes) ---" << std::endl;

    Kruskal k(N);
    for (int i = 0; i < N * 4; ++i) {
        k.add_edge(rand() % N, rand() % N, rand() % 1000);
    }

    lab::print_qor("Initial Graph", k.memory_usage());

    long long weight = 0;
    {
        lab::Benchmark b("Kruskal's Algorithm");
        weight = k.solve();
    }

    lab::print_qor("Final Result", k.memory_usage(), (size_t)weight);
    std::cout << "[METRICS] MST Total Weight: " << weight << std::endl;

    return 0;
}
