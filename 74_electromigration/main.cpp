/**
 * EXPERIMENT: Electromigration (EM) Checking
 * 
 * GOAL: Calculate current density in wires and estimate MTTF 
 * (Mean Time To Failure) using Black's Law.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

struct WireEM {
    float width; // nm
    float current; // mA
    float temperature; // K
};

class EMChecker {
    float J_limit = 1.0e6f; // Simplified limit A/cm^2
    float Ea = 0.7f; // Activation energy (eV)
    float k = 8.617e-5f; // Boltzmann constant

public:
    float calculate_mttf(const WireEM& w) {
        // Black's Law: MTTF = A * J^-n * exp(Ea / kT)
        float J = (w.current * 1e-3f) / (w.width * 1e-7f * 1e-7f); // Simplified J
        float mttf = (1.0f / (J * J)) * std::exp(Ea / (k * w.temperature));
        return mttf;
    }
};

int main() {
    std::cout << "--- Electromigration Checking Laboratory ---" << std::endl;

    EMChecker checker;
    WireEM w1 = {100.0f, 0.5f, 373.0f}; // Hot, narrow wire
    WireEM w2 = {200.0f, 0.5f, 323.0f}; // Cool, wide wire

    {
        lab::Benchmark b("EM MTTF Calculation");
        float mttf1 = checker.calculate_mttf(w1);
        float mttf2 = checker.calculate_mttf(w2);
        std::cout << "[METRICS] Wire 1 MTTF: " << mttf1 << " hrs" << std::endl;
        std::cout << "[METRICS] Wire 2 MTTF: " << mttf2 << " hrs" << std::endl;
        std::cout << "[METRICS] Reliability Ratio: " << mttf2 / mttf1 << "x" << std::endl;
    }

    lab::print_qor("EM Metadata", sizeof(WireEM) * 2);

    return 0;
}
