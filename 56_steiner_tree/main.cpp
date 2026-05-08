/**
 * EXPERIMENT: Rectilinear Steiner Minimum Tree (RSMT) Heuristic
 * 
 * GOAL: Use an MST-based heuristic to approximate the shortest 
 * rectilinear tree connecting a set of pins.
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

struct Point { int x, y; };
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const { return weight < other.weight; }
};

class SteinerHeuristic {
    std::vector<Point> pins;
    std::vector<int> parent;

public:
    SteinerHeuristic(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    void add_pin(int x, int y) { pins.push_back({x, y}); }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int r_i = find(i);
        int r_j = find(j);
        if (r_i != r_j) {
            parent[r_i] = r_j;
            return true;
        }
        return false;
    }

    int compute_mst_wirelength() {
        std::vector<Edge> edges;
        int n = pins.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = std::abs(pins[i].x - pins[j].x) + std::abs(pins[i].y - pins[j].y);
                edges.push_back({i, j, dist});
            }
        }
        std::sort(edges.begin(), edges.end());

        int total = 0;
        for (const auto& e : edges) {
            if (unite(e.u, e.v)) total += e.weight;
        }
        return total;
    }

    size_t memory_usage() const { return pins.size() * sizeof(Point) + parent.size() * sizeof(int); }
};

int main() {
    int PINS = 500;
    std::cout << "--- RSMT Heuristic Laboratory (" << PINS << " pins) ---" << std::endl;

    SteinerHeuristic sh(PINS);
    for (int i = 0; i < PINS; ++i) sh.add_pin(rand() % 1000, rand() % 1000);

    lab::print_qor("Pin Layout", sh.memory_usage());

    int wl = 0;
    {
        lab::Benchmark b("MST-based RSMT Approximation");
        wl = sh.compute_mst_wirelength();
    }

    std::cout << "[METRICS] Estimated Wirelength (MST): " << wl << std::endl;
    lab::print_qor("Final Steiner", 0, (size_t)wl);

    return 0;
}
