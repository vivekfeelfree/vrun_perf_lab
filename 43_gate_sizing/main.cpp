/**
 * EXPERIMENT: Gate Sizing
 * 
 * GOAL: Optimize a mapped netlist by choosing gate sizes to 
 * satisfy timing constraints while minimizing area.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Cell {
    float area;
    float delay;
};

struct Instance {
    std::vector<Cell> library;
    int selected_size;
    float arrival_time;
};

class SizingEngine {
    std::vector<Instance> netlist;

public:
    void add_instance(const std::vector<Cell>& lib) {
        netlist.push_back({lib, 0, 0.0f}); // Default to smallest (index 0)
    }

    void compute_timing() {
        float curr_time = 0;
        for (auto& inst : netlist) {
            inst.arrival_time = curr_time + inst.library[inst.selected_size].delay;
            curr_time = inst.arrival_time;
        }
    }

    void optimize(float target_delay) {
        // Greedy: find the instance where sizing up gives the best delay reduction per area increase
        for (int i = 0; i < 100; ++i) { // Iterative refinement
            compute_timing();
            if (netlist.back().arrival_time <= target_delay) break;

            int best_idx = -1;
            float best_gain = 0;

            for (int j = 0; j < (int)netlist.size(); ++j) {
                auto& inst = netlist[j];
                if (inst.selected_size + 1 < (int)inst.library.size()) {
                    float d_delay = inst.library[inst.selected_size].delay - inst.library[inst.selected_size+1].delay;
                    float d_area = inst.library[inst.selected_size+1].area - inst.library[inst.selected_size].area;
                    float gain = d_delay / d_area;
                    if (gain > best_gain) {
                        best_gain = gain;
                        best_idx = j;
                    }
                }
            }

            if (best_idx != -1) {
                netlist[best_idx].selected_size++;
            } else break;
        }
    }

    float total_area() {
        float a = 0;
        for (const auto& inst : netlist) a += inst.library[inst.selected_size].area;
        return a;
    }

    float total_delay() { return netlist.back().arrival_time; }
};

int main() {
    std::cout << "--- Gate Sizing Laboratory ---" << std::endl;

    std::vector<Cell> lib = {{1.0, 10.0}, {2.0, 5.0}, {4.0, 2.0}}; // Small, Med, Large
    SizingEngine engine;
    for (int i = 0; i < 50; ++i) engine.add_instance(lib);

    engine.compute_timing();
    std::cout << "[METRICS] Initial Area: " << engine.total_area() << " | Delay: " << engine.total_delay() << std::endl;

    float target = 300.0f;
    {
        lab::Benchmark b("Greedy Gate Sizing");
        engine.optimize(target);
    }

    std::cout << "[METRICS] Optimized Area: " << engine.total_area() << " | Delay: " << engine.total_delay() << std::endl;
    lab::print_qor("Sizing Metrics", (size_t)engine.total_area(), (size_t)engine.total_delay());

    return 0;
}
