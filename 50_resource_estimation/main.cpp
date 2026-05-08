/**
 * EXPERIMENT: Resource Estimation
 * 
 * GOAL: Predict hardware resource utilization (LUTs, FFs, DSPs) for 
 * a behavioral description before full synthesis.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>

struct ResourceEstimate {
    int luts;
    int ffs;
    int dsps;
};

class ResourceEstimator {
public:
    ResourceEstimate estimate_multiplier(int width) {
        // Simple model: N-bit multiplier uses roughly (N/18)^2 DSPs on some FPGAs
        // and some extra LUTs for routing.
        int dsps = (width + 17) / 18;
        dsps *= dsps;
        int luts = width * width / 2;
        return {luts, 0, dsps};
    }

    ResourceEstimate estimate_counter(int width) {
        return {width, width, 0};
    }
};

int main() {
    std::cout << "--- Resource Estimation Laboratory ---" << std::endl;

    ResourceEstimator estimator;
    ResourceEstimate mult32, count16;

    {
        lab::Benchmark b("Estimation: 32-bit Mult");
        mult32 = estimator.estimate_multiplier(32);
    }
    std::cout << "[METRICS] 32-bit Multiplier: LUTs=" << mult32.luts << ", DSPs=" << mult32.dsps << std::endl;

    {
        lab::Benchmark b("Estimation: 16-bit Counter");
        count16 = estimator.estimate_counter(16);
    }
    std::cout << "[METRICS] 16-bit Counter: LUTs=" << count16.luts << ", FFs=" << count16.ffs << std::endl;

    lab::print_qor("Resource Prediction", sizeof(ResourceEstimate) * 2);

    return 0;
}
