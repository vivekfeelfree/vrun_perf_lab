/**
 * EXPERIMENT: Traveling Salesman Problem (TSP) via Simulated Annealing
 * 
 * GOAL: Use Simulated Annealing to find a near-optimal tour through 
 * a set of points, minimizing total Euclidean distance.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

struct Point { float x, y; };

class TSPSolver {
    std::vector<Point> points;
    std::vector<int> tour;
    float current_dist;

public:
    TSPSolver(int n) {
        for (int i = 0; i < n; ++i) {
            points.push_back({(float)(rand() % 1000), (float)(rand() % 1000)});
            tour.push_back(i);
        }
        std::shuffle(tour.begin(), tour.end(), std::mt19937(42));
        current_dist = calculate_distance(tour);
    }

    float calculate_distance(const std::vector<int>& t) {
        float d = 0;
        for (size_t i = 0; i < t.size(); ++i) {
            int u = t[i];
            int v = t[(i + 1) % t.size()];
            d += std::sqrt(std::pow(points[u].x - points[v].x, 2) + std::pow(points[u].y - points[v].y, 2));
        }
        return d;
    }

    void solve(int iterations) {
        float temp = 1000.0f;
        float cooling = 0.999f;
        std::mt19937 gen(42);
        std::uniform_real_distribution<float> dis(0, 1);

        for (int i = 0; i < iterations; ++i) {
            int a = rand() % tour.size();
            int b = rand() % tour.size();
            if (a == b) continue;

            std::vector<int> next_tour = tour;
            std::swap(next_tour[a], next_tour[b]);
            float next_dist = calculate_distance(next_tour);

            if (next_dist < current_dist || dis(gen) < std::exp((current_dist - next_dist) / temp)) {
                current_dist = next_dist;
                tour = next_tour;
            }
            temp *= cooling;
        }
    }

    float get_dist() { return current_dist; }
    size_t memory_usage() const { return points.size() * sizeof(Point) + tour.size() * sizeof(int); }
};

int main() {
    int N = 100;
    std::cout << "--- TSP (Simulated Annealing) Laboratory (" << N << " cities) ---" << std::endl;

    TSPSolver solver(N);
    std::cout << "[METRICS] Initial Distance: " << solver.get_dist() << std::endl;
    lab::print_qor("Initial State", solver.memory_usage());

    {
        lab::Benchmark b("TSP SA Optimization (100k iterations)");
        solver.solve(100000);
    }

    std::cout << "[METRICS] Optimized Distance: " << solver.get_dist() << std::endl;
    lab::print_qor("Final State", solver.memory_usage(), (size_t)solver.get_dist());

    return 0;
}
