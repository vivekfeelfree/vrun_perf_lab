/**
 * EXPERIMENT: Floorplanning via Simulated Annealing
 * 
 * GOAL: Optimize the placement of macro blocks to minimize a 
 * weighted sum of Total Area and Wirelength.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

struct Block {
    int w, h, x, y;
};

class Floorplanner {
    std::vector<Block> blocks;
    float current_cost;

public:
    Floorplanner(int n) {
        for (int i = 0; i < n; ++i) {
            blocks.push_back({rand() % 10 + 1, rand() % 10 + 1, 0, 0});
        }
        current_cost = compute_cost();
    }

    float compute_cost() {
        // Very simplified: sum of bounding box area
        int max_x = 0, max_y = 0;
        for (const auto& b : blocks) {
            max_x = std::max(max_x, b.x + b.w);
            max_y = std::max(max_y, b.y + b.h);
        }
        return (float)max_x * max_y;
    }

    void move() {
        int idx = rand() % blocks.size();
        blocks[idx].x = rand() % 50;
        blocks[idx].y = rand() % 50;
    }

    void run_sa(int iterations) {
        float temp = 1000.0f;
        float cooling = 0.99f;
        std::mt19937 gen(42);
        std::uniform_real_distribution<float> dis(0, 1);

        for (int i = 0; i < iterations; ++i) {
            std::vector<Block> old_blocks = blocks;
            move();
            float new_cost = compute_cost();
            
            if (new_cost < current_cost || dis(gen) < std::exp((current_cost - new_cost) / temp)) {
                current_cost = new_cost;
            } else {
                blocks = old_blocks;
            }
            temp *= cooling;
        }
    }

    float get_cost() { return current_cost; }
    size_t memory_usage() const { return blocks.size() * sizeof(Block); }
};

int main() {
    std::cout << "--- Floorplanning (Simulated Annealing) Laboratory ---" << std::endl;

    Floorplanner fp(20);
    lab::print_qor("Initial State", fp.memory_usage());
    std::cout << "[METRICS] Initial Cost: " << fp.compute_cost() << std::endl;

    {
        lab::Benchmark b("Simulated Annealing Optimization");
        fp.run_sa(10000);
    }

    std::cout << "[METRICS] Optimized Cost: " << fp.get_cost() << std::endl;
    lab::print_qor("Final State", fp.memory_usage(), (size_t)fp.get_cost());

    return 0;
}
