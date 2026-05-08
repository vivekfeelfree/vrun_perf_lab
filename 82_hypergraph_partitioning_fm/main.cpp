/**
 * EXPERIMENT: Hypergraph Partitioning (Fiduccia-Mattheyses)
 * 
 * GOAL: Implement the FM heuristic to minimize the cut-size of a 
 * hypergraph, a standard algorithm for netlist partitioning.
 */

#include "../include/harness.hpp"
#include <vector>
#include <map>
#include <algorithm>

struct Hyperedge {
    std::vector<int> nodes;
};

class FMPartitioner {
    int n_nodes;
    std::vector<Hyperedge> edges;
    std::vector<int> partition; // 0 or 1

public:
    FMPartitioner(int n) : n_nodes(n), partition(n) {
        for (int i = 0; i < n; ++i) partition[i] = i % 2;
    }

    void add_edge(const std::vector<int>& nodes) { edges.push_back({nodes}); }

    int compute_cut() {
        int cut = 0;
        for (const auto& e : edges) {
            int p0 = 0, p1 = 0;
            for (int n : e.nodes) {
                if (partition[n] == 0) p0++; else p1++;
            }
            if (p0 > 0 && p1 > 0) cut++;
        }
        return cut;
    }

    void solve(int passes) {
        for (int p = 0; p < passes; ++p) {
            std::vector<bool> locked(n_nodes, false);
            for (int i = 0; i < n_nodes; ++i) {
                // Simplified FM: find node with best gain
                int best_node = -1;
                int max_gain = -1e9;

                for (int j = 0; j < n_nodes; ++j) {
                    if (locked[j]) continue;
                    
                    int initial_cut = compute_cut();
                    partition[j] = 1 - partition[j];
                    int gain = initial_cut - compute_cut();
                    partition[j] = 1 - partition[j]; // Revert

                    if (gain > max_gain) {
                        max_gain = gain;
                        best_node = j;
                    }
                }

                if (best_node != -1) {
                    partition[best_node] = 1 - partition[best_node];
                    locked[best_node] = true;
                }
            }
        }
    }

    size_t memory_usage() const { 
        size_t total = partition.size() * sizeof(int);
        for (const auto& e : edges) total += e.nodes.size() * sizeof(int);
        return total;
    }
};

int main() {
    int N = 100, E = 200;
    std::cout << "--- Hypergraph Partitioning (FM) Laboratory ---" << std::endl;

    FMPartitioner fm(N);
    for (int i = 0; i < E; ++i) {
        std::vector<int> edge;
        for (int j = 0; j < 3; ++j) edge.push_back(rand() % N);
        fm.add_edge(edge);
    }

    std::cout << "[METRICS] Initial Cut: " << fm.compute_cut() << std::endl;
    lab::print_qor("Initial Design", fm.memory_usage());

    {
        lab::Benchmark b("FM Partitioning (2 passes)");
        fm.solve(2);
    }

    std::cout << "[METRICS] Final Cut:   " << fm.compute_cut() << std::endl;
    lab::print_qor("Final Design", fm.memory_usage(), fm.compute_cut());

    return 0;
}
