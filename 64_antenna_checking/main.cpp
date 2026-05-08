/**
 * EXPERIMENT: Antenna Effect Checking
 * 
 * GOAL: Calculate metal-to-gate area ratios for nets to identify 
 * potential antenna violations.
 */

#include "../include/harness.hpp"
#include <vector>
#include <iostream>

struct Net {
    int id;
    float metal_area;
    float gate_area;
};

class AntennaChecker {
    std::vector<Net> nets;
    float max_ratio = 100.0f; // Simplified threshold

public:
    void add_net(int id, float metal, float gate) {
        nets.push_back({id, metal, gate});
    }

    int check_violations() {
        int violations = 0;
        for (const auto& net : nets) {
            if (net.gate_area > 0) {
                float ratio = net.metal_area / net.gate_area;
                if (ratio > max_ratio) violations++;
            }
        }
        return violations;
    }

    size_t memory_usage() const { return nets.size() * sizeof(Net); }
};

int main() {
    int NETS = 10000;
    std::cout << "--- Antenna Effect Checking Laboratory ---" << std::endl;

    AntennaChecker checker;
    for (int i = 0; i < NETS; ++i) {
        float metal = (float)(rand() % 5000);
        float gate = (float)(rand() % 50 + 1);
        checker.add_net(i, metal, gate);
    }

    lab::print_qor("Netlist Database", checker.memory_usage());

    int violations = 0;
    {
        lab::Benchmark b("Antenna Rule Check");
        violations = checker.check_violations();
    }

    std::cout << "[METRICS] Antenna Violations: " << violations << std::endl;
    lab::print_qor("Final Results", 0, violations);

    return 0;
}
