/**
 * EXPERIMENT: Metal Fill & Density Optimization
 * 
 * GOAL: Add "dummy" metal fill to a layout to meet density requirements 
 * for Chemical Mechanical Polishing (CMP).
 */

#include "../include/harness.hpp"
#include <vector>

class DensityManager {
    int N; // Chip area divided into N x N bins
    std::vector<float> density;
    float target_density = 0.35f;

public:
    DensityManager(int n) : N(n), density(n * n, 0.0f) {
        // Initial random metal distribution
        for (int i = 0; i < N * N; ++i) density[i] = (float)(rand() % 20) / 100.0f;
    }

    int add_metal_fill() {
        int fill_added = 0;
        for (int i = 0; i < N * N; ++i) {
            if (density[i] < target_density) {
                density[i] = target_density;
                fill_added++;
            }
        }
        return fill_added;
    }

    size_t memory_usage() const { return density.size() * sizeof(float); }
};

int main() {
    int BINS = 500;
    std::cout << "--- Metal Fill & Density Laboratory (" << BINS << "x" << BINS << ") ---" << std::endl;

    DensityManager dm(BINS);
    lab::print_qor("Density Map", dm.memory_usage());

    int units = 0;
    {
        lab::Benchmark b("Metal Fill Insertion");
        units = dm.add_metal_fill();
    }

    std::cout << "[METRICS] Bins Requiring Fill: " << units << std::endl;
    lab::print_qor("Final Density", 0, units);

    return 0;
}
