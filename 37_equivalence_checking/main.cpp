/**
 * EXPERIMENT: Combinational Equivalence Checking (CEC)
 * 
 * GOAL: Use random simulation to identify non-equivalent points 
 * between two logic designs.
 */

#include "../include/harness.hpp"
#include <vector>
#include <random>

class MiterSimulator {
    int n_pi;
    struct Gate { int f1, f2; bool inv1, inv2; };
    std::vector<Gate> circuit1, circuit2;

public:
    MiterSimulator(int pi) : n_pi(pi) {}

    void add_gate1(int f1, bool i1, int f2, bool i2) { circuit1.push_back({f1, f2, i1, i2}); }
    void add_gate2(int f1, bool i1, int f2, bool i2) { circuit2.push_back({f1, f2, i1, i2}); }

    bool simulate(const std::vector<bool>& inputs) {
        auto run = [&](const std::vector<Gate>& c) {
            std::vector<bool> vals = inputs;
            for (const auto& g : c) {
                bool v1 = vals[g.f1] ^ g.inv1;
                bool v2 = vals[g.f2] ^ g.inv2;
                vals.push_back(v1 && v2);
            }
            return vals.back();
        };

        return run(circuit1) != run(circuit2); // XOR miter
    }

    int run_random_sim(int patterns) {
        int bugs = 0;
        std::mt19937 gen(42);
        std::uniform_int_distribution<> dis(0, 1);

        for (int i = 0; i < patterns; ++i) {
            std::vector<bool> inputs(n_pi);
            for (int j = 0; j < n_pi; ++j) inputs[j] = dis(gen);
            if (simulate(inputs)) bugs++;
        }
        return bugs;
    }
};

int main() {
    int PI = 16;
    std::cout << "--- Combinational Equivalence Checking Laboratory ---" << std::endl;

    MiterSimulator miter(PI);
    // Design 1: (A & B) & C
    miter.add_gate1(0, false, 1, false);
    miter.add_gate1(PI, false, 2, false);

    // Design 2: A & (B & C) -> Equivalent
    miter.add_gate2(1, false, 2, false);
    miter.add_gate2(0, false, PI, false);

    {
        lab::Benchmark b("CEC Random Simulation (Equivalent)");
        int bugs = miter.run_random_sim(10000);
        std::cout << "[METRICS] Mismatching Patterns: " << bugs << std::endl;
    }

    // Design 3: A & (B & !C) -> Non-Equivalent
    MiterSimulator miter2(PI);
    miter2.add_gate1(0, false, 1, false);
    miter2.add_gate1(PI, false, 2, false);

    miter2.add_gate2(1, false, 2, true); // Bug here
    miter2.add_gate2(0, false, PI, false);

    {
        lab::Benchmark b("CEC Random Simulation (Non-Equivalent)");
        int bugs = miter2.run_random_sim(10000);
        std::cout << "[METRICS] Mismatching Patterns: " << bugs << std::endl;
    }

    return 0;
}
