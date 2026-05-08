/**
 * EXPERIMENT: Thermal Analysis (2D Heat Diffusion)
 * 
 * GOAL: Simulate temperature distribution across a chip using a 
 * simple 2D finite-difference heat diffusion model.
 */

#include "../include/harness.hpp"
#include <vector>

class ThermalSimulator {
    int N;
    std::vector<float> T;
    std::vector<float> Power;

public:
    ThermalSimulator(int n) : N(n), T(n * n, 300.0f), Power(n * n, 0.0f) {
        // Add a heat source in the middle
        for (int i = N / 2 - 5; i < N / 2 + 5; ++i) {
            for (int j = N / 2 - 5; j < N / 2 + 5; ++j) Power[i * N + j] = 5.0f;
        }
    }

    void step() {
        std::vector<float> next_T = T;
        float alpha = 0.01f; // Diffusion constant
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < N - 1; ++j) {
                float neighbors = T[(i - 1) * N + j] + T[(i + 1) * N + j] + 
                                 T[i * N + (j - 1)] + T[i * N + (j + 1)];
                next_T[i * N + j] = T[i * N + j] + alpha * (neighbors - 4 * T[i * N + j]) + Power[i * N + j];
            }
        }
        T = next_T;
    }

    float max_temp() {
        float m = 0;
        for (float t : T) if (t > m) m = t;
        return m;
    }

    size_t memory_usage() const { return T.size() * sizeof(float) * 2; }
};

int main() {
    int GRID = 50;
    std::cout << "--- Thermal Analysis Laboratory (" << GRID << "x" << GRID << ") ---" << std::endl;

    ThermalSimulator sim(GRID);
    lab::print_qor("Thermal Grid", sim.memory_usage());

    {
        lab::Benchmark b("Heat Diffusion (500 steps)");
        for (int i = 0; i < 500; ++i) sim.step();
    }

    std::cout << "[METRICS] Maximum Junction Temperature: " << sim.max_temp() << " K" << std::endl;
    lab::print_qor("Final Temp", 0, (size_t)sim.max_temp());

    return 0;
}
