/**
 * EXPERIMENT: Graph Coloring (DSATUR Heuristic)
 * 
 * GOAL: Use the Degree of Saturation (DSATUR) heuristic to color 
 * a graph with a near-minimum number of colors.
 */

#include "../include/harness.hpp"
#include <vector>
#include <set>
#include <algorithm>

class DSATURColorer {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> color;
    std::vector<std::set<int>> sat_colors; // Set of colors assigned to neighbors

public:
    DSATURColorer(int nodes) : n(nodes), adj(nodes), color(nodes, -1), sat_colors(nodes) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int solve() {
        for (int step = 0; step < n; ++step) {
            // Find node with max degree of saturation
            int best_node = -1;
            int max_sat = -1;
            int max_deg = -1;

            for (int i = 0; i < n; ++i) {
                if (color[i] != -1) continue;
                int curr_sat = sat_colors[i].size();
                int curr_deg = adj[i].size();
                if (curr_sat > max_sat || (curr_sat == max_sat && curr_deg > max_deg)) {
                    max_sat = curr_sat;
                    max_deg = curr_deg;
                    best_node = i;
                }
            }

            // Assign lowest available color
            std::set<int> neighbor_colors;
            for (int neighbor : adj[best_node]) {
                if (color[neighbor] != -1) neighbor_colors.insert(color[neighbor]);
            }

            int c = 0;
            while (neighbor_colors.count(c)) c++;
            color[best_node] = c;

            // Update neighbors' saturation
            for (int neighbor : adj[best_node]) {
                sat_colors[neighbor].insert(c);
            }
        }

        int max_c = 0;
        for (int c : color) if (c > max_c) max_c = c;
        return max_c + 1;
    }

    size_t memory_usage() const { return n * sizeof(int) + n * sizeof(std::set<int>); }
};

int main() {
    int N = 500;
    std::cout << "--- Graph Coloring (DSATUR) Laboratory (" << N << " nodes) ---" << std::endl;

    DSATURColorer colorer(N);
    for (int i = 0; i < N * 5; ++i) {
        colorer.add_edge(rand() % N, rand() % N);
    }

    lab::print_qor("Graph Infrastructure", colorer.memory_usage());

    int colors = 0;
    {
        lab::Benchmark b("DSATUR Graph Coloring");
        colors = colorer.solve();
    }

    std::cout << "[METRICS] Colors Used (Chromatic Number): " << colors << std::endl;
    lab::print_qor("Final Coloring", 0, colors);

    return 0;
}
