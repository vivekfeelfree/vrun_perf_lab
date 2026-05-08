/**
 * EXPERIMENT: Yield Analysis (Monte Carlo Simulation)
 * 
 * GOAL: Estimate the percentage of chips that meet timing 
 * specifications under process variations using Monte Carlo simulation.
 */

#include "../include/harness.hpp"
#include <vector>
#include <random>

class YieldAnalyzer {
    float nominal_delay;
    float std_dev;
    float spec_limit;

public:
    YieldAnalyzer(float nom, float sd, float limit) 
        : nominal_delay(nom), std_dev(sd), spec_limit(limit) {}

    float run_monte_carlo(int trials) {
        int passed = 0;
        std::mt19937 gen(42);
        std::normal_distribution<float> dist(nominal_delay, std_dev);

        for (int i = 0; i < trials; ++i) {
            if (dist(gen) <= spec_limit) {
                passed++;
            }
        }
        return (float)passed / trials * 100.0f;
    }
};

int main() {
    int TRIALS = 100000;
    std::cout << "--- Yield Analysis (Monte Carlo) Laboratory ---" << std::endl;

    // Spec: Delay <= 1.5ns, Nominal: 1.4ns, StdDev: 0.05ns
    YieldAnalyzer analyzer(1.4f, 0.05f, 1.5f);

    float yield = 0;
    {
        lab::Benchmark b("Monte Carlo Yield Estimation");
        yield = analyzer.run_monte_carlo(TRIALS);
    }

    std::cout << "[METRICS] Estimated Yield: " << yield << "%" << std::endl;
    lab::print_qor("Yield Metrics", 0, (size_t)yield);

    return 0;
}
