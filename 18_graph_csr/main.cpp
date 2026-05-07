/**
 * EXPERIMENT: Graph Representations (CSR vs. Adjacency Lists)
 * 
 * GOAL: Demonstrate the cache-locality benefits of CSR for large 
 * graph traversals.
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>
#include <random>

/**
 * Naive Adjacency List: Array of Vectors
 */
struct NaiveGraph {
    std::vector<std::vector<int>> adj;

    NaiveGraph(int nodes) : adj(nodes) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    long long sum_neighbors() const {
        long long sum = 0;
        for (const auto& neighbors : adj) {
            for (int v : neighbors) {
                sum += v;
            }
        }
        return sum;
    }
};

/**
 * Optimized: Compressed Sparse Row (CSR)
 */
struct CSRGraph {
    std::vector<int> edges;
    std::vector<size_t> offsets;

    CSRGraph(const NaiveGraph& naive) {
        offsets.push_back(0);
        for (const auto& neighbors : naive.adj) {
            for (int v : neighbors) {
                edges.push_back(v);
            }
            offsets.push_back(edges.size());
        }
    }

    long long sum_neighbors() const {
        long long sum = 0;
        for (size_t i = 0; i < offsets.size() - 1; ++i) {
            size_t start = offsets[i];
            size_t end = offsets[i+1];
            for (size_t j = start; j < end; ++j) {
                sum += edges[j];
            }
        }
        return sum;
    }
};

const int NUM_NODES = 1'000'000;
const int EDGES_PER_NODE = 10;

int main() {
    std::cout << "--- Graph Laboratory (" << NUM_NODES << " nodes) ---" << std::endl;

    NaiveGraph naive(NUM_NODES);
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(0, NUM_NODES - 1);

    // Build the graph
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = 0; j < EDGES_PER_NODE; ++j) {
            naive.add_edge(i, dis(gen));
        }
    }

    // Convert to CSR
    CSRGraph csr(naive);

    {
        lab::Benchmark b("Naive Adjacency List (Sum)");
        long long sum = naive.sum_neighbors();
        lab::escape(&sum);
    }

    {
        lab::Benchmark b("CSR (Compressed Sparse Row)");
        long long sum = csr.sum_neighbors();
        lab::escape(&sum);
    }

    return 0;
}
