/**
 * EXPERIMENT: Soft Error Rate (SER) Analysis
 * 
 * GOAL: Estimate the susceptibility of sequential elements to 
 * particle strikes (single-event upsets) based on node capacitance.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

class SERAnalyzer {
public:
    float estimate_fit(float capacitance, float voltage) {
        // FIT (Failures In Time) = 10^9 hours
        // Simplistic model: lower capacitance/voltage increases SER
        float fit = 100.0f * std::exp(-capacitance * voltage);
        return fit;
    }
};

int main() {
    std::cout << "--- Soft Error Rate (SER) Analysis Laboratory ---" << std::endl;

    SERAnalyzer ser;
    float c1 = 1.0f, v1 = 0.8f; // Low power node
    float c2 = 5.0f, v2 = 1.2f; // High reliability node

    {
        lab::Benchmark b("SER FIT Estimation");
        float fit1 = ser.estimate_fit(c1, v1);
        float fit2 = ser.estimate_fit(c2, v2);
        std::cout << "[METRICS] FIT (Node 1): " << fit1 << std::endl;
        std::cout << "[METRICS] FIT (Node 2): " << fit2 << std::endl;
        std::cout << "[METRICS] SER Improvement: " << fit1 / fit2 << "x" << std::endl;
    }

    lab::print_qor("SER Stats", sizeof(SERAnalyzer));

    return 0;
}
