/**
 * EXPERIMENT: Power Grid Analysis (IR Drop)
 * 
 * GOAL: Calculate voltage drops across a power grid using an 
 * iterative Gauss-Seidel solver.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

class PowerGrid {
    int N; // Grid size (N x N)
    std::vector<float> V;
    std::vector<float> I; // Current sources at each node
    float R = 0.1f; // Resistance between nodes

public:
    PowerGrid(int n) : N(n), V(n * n, 1.2f), I(n * n, 0.0f) {
        // Simple current source distribution (some hot spots)
        for (int i = 0; i < N * N; ++i) {
            if (rand() % 10 == 0) I[i] = 0.01f;
        }
    }

    void solve(int iterations) {
        for (int iter = 0; iter < iterations; ++iter) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
                        V[i * N + j] = 1.2f; // VDD pads at boundaries
                        continue;
                    }
                    // Gauss-Seidel step: V = (sum(V_neighbors)/R + I) / (4/R)
                    float neighbors = V[(i - 1) * N + j] + V[(i + 1) * N + j] + 
                                     V[i * N + (j - 1)] + V[i * N + (j + 1)];
                    V[i * N + j] = (neighbors / R - I[i * N + j]) / (4.0f / R);
                }
            }
        }
    }

    float worst_drop() {
        float min_v = 1.2f;
        for (float v : V) if (v < min_v) min_v = v;
        return 1.2f - min_v;
    }

    size_t memory_usage() const { return V.size() * sizeof(float) * 2; }
};

int main() {
    int GRID_SIZE = 100;
    std::cout << "--- Power Grid (IR Drop) Laboratory (" << GRID_SIZE << "x" << GRID_SIZE << ") ---" << std::endl;

    PowerGrid pg(GRID_SIZE);
    lab::print_qor("Grid Layout", pg.memory_usage());

    {
        lab::Benchmark b("Gauss-Seidel Solver (100 iterations)");
        pg.solve(100);
    }

    std::cout << "[METRICS] Worst-Case IR Drop: " << pg.worst_drop() << " V" << std::endl;
    lab::print_qor("Final Analysis", 0, (size_t)(pg.worst_drop() * 1000));

    return 0;
}
