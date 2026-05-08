/**
 * EXPERIMENT: Cycle-Based Logic Simulation
 * 
 * GOAL: Demonstrate high-throughput simulation using bit-parallel 
 * (SWAR) techniques to process 64 patterns at once.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cstdint>

struct Gate {
    int f1, f2;
};

class CycleSimulator {
    std::vector<Gate> gates;
    std::vector<uint64_t> values;
    int n_pi;

public:
    CycleSimulator(int pi) : n_pi(pi), values(pi) {}

    void add_gate(int f1, int f2) {
        gates.push_back({f1, f2});
        values.push_back(0);
    }

    void simulate() {
        for (size_t i = 0; i < gates.size(); ++i) {
            values[n_pi + i] = values[gates[i].f1] & values[gates[i].f2];
        }
    }

    void set_pi(int idx, uint64_t val) { values[idx] = val; }

    size_t memory_usage() const {
        return gates.size() * sizeof(Gate) + values.size() * sizeof(uint64_t);
    }
};

int main() {
    int PI = 100;
    int GATES = 10000;
    std::cout << "--- Cycle-Based (Bit-Parallel) Simulation Laboratory ---" << std::endl;

    CycleSimulator sim(PI);
    for (int i = 0; i < GATES; ++i) {
        sim.add_gate(rand() % (PI + i), rand() % (PI + i));
    }

    lab::print_qor("Simulator Footprint", sim.memory_usage());

    {
        lab::Benchmark b("Bit-Parallel Simulation (10k cycles x 64)");
        for (int i = 0; i < 10000; ++i) {
            for (int j = 0; j < PI; ++j) sim.set_pi(j, (uint64_t)rand() << 32 | rand());
            sim.simulate();
        }
    }

    std::cout << "[METRICS] Total Boolean Operations: " << (long long)GATES * 10000 * 64 << std::endl;

    return 0;
}
