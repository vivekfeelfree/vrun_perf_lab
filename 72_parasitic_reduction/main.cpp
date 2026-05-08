/**
 * EXPERIMENT: Parasitic RC Reduction (Pi-Model)
 * 
 * GOAL: Simplify a detailed RC tree into a 3-element Pi-model 
 * that preserves the first two moments of the circuit response.
 */

#include "../include/harness.hpp"
#include <vector>

struct PiModel {
    float C1, R, C2;
};

class ParasiticReducer {
public:
    PiModel reduce_chain(float total_r, float total_c) {
        // Simplified A-law reduction: split capacitance equally
        // and put resistance in the middle.
        return {total_c / 2.0f, total_r, total_c / 2.0f};
    }
};

int main() {
    std::cout << "--- Parasitic RC Reduction Laboratory ---" << std::endl;

    ParasiticReducer reducer;
    float R_total = 50.0f; // Ohms
    float C_total = 100.0f; // fF

    PiModel pi;
    {
        lab::Benchmark b("Pi-Model Reduction");
        pi = reducer.reduce_chain(R_total, C_total);
    }

    std::cout << "[METRICS] Reduced Pi-Model: C1=" << pi.C1 << "fF, R=" << pi.R << "Ohm, C2=" << pi.C2 << "fF" << std::endl;
    lab::print_qor("RC Metrics", 0, (size_t)pi.R);

    return 0;
}
