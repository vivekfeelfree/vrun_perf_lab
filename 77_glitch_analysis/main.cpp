/**
 * EXPERIMENT: Glitch Analysis (Hazard Detection)
 * 
 * GOAL: Identify potential static hazards (glitches) in combinational 
 * logic due to unequal path delays.
 */

#include "../include/harness.hpp"
#include <vector>
#include <iostream>

struct Gate {
    int f1, f2;
    float delay1, delay2;
};

class GlitchAnalyzer {
    std::vector<Gate> gates;

public:
    void add_gate(int f1, float d1, int f2, float d2) {
        gates.push_back({f1, f2, d1, d2});
    }

    int find_hazards() {
        int hazards = 0;
        for (const auto& g : gates) {
            // If the delay difference between inputs is large, a hazard is likely
            if (std::abs(g.delay1 - g.delay2) > 0.5f) {
                hazards++;
            }
        }
        return hazards;
    }
};

int main() {
    std::cout << "--- Glitch Analysis Laboratory ---" << std::endl;

    GlitchAnalyzer analyzer;
    analyzer.add_gate(0, 0.1f, 1, 0.7f); // Potential glitch
    analyzer.add_gate(2, 0.3f, 3, 0.4f); // Safe

    int hazards = 0;
    {
        lab::Benchmark b("Static Hazard Detection");
        hazards = analyzer.find_hazards();
    }

    std::cout << "[METRICS] Potential Logic Glitches: " << hazards << std::endl;
    lab::print_qor("Glitch DB", sizeof(analyzer), hazards);

    return 0;
}
