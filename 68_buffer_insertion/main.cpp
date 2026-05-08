/**
 * EXPERIMENT: Timing Closure via Buffer Insertion
 * 
 * GOAL: Reduce wire delay on critical paths by inserting buffers 
 * at optimal intervals to break up long RC chains.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

class TimingOptimizer {
    float R_per_unit = 0.5f;
    float C_per_unit = 1.0f;
    float buf_delay = 10.0f;

public:
    struct Result { int buffers; float delay; };

    Result optimize_wire(float length) {
        // Delay without buffers: 0.5 * R * C * L^2
        float initial_delay = 0.5f * (R_per_unit * length) * (C_per_unit * length);
        
        float best_delay = initial_delay;
        int best_buffers = 0;

        // Try adding 1 to 10 buffers
        for (int n = 1; n <= 10; ++n) {
            float segment_len = length / (n + 1);
            float segment_delay = 0.5f * (R_per_unit * segment_len) * (C_per_unit * segment_len);
            float total_delay = (n + 1) * segment_delay + n * buf_delay;
            
            if (total_delay < best_delay) {
                best_delay = total_delay;
                best_buffers = n;
            }
        }
        return {best_buffers, best_delay};
    }
};

int main() {
    float WIRE_LEN = 100.0f;
    std::cout << "--- Timing Closure (Buffer Insertion) Laboratory ---" << std::endl;

    TimingOptimizer opt;
    TimingOptimizer::Result res;

    float initial_delay = 0.5f * 0.5f * 1.0f * WIRE_LEN * WIRE_LEN;
    std::cout << "[METRICS] Initial Wire Delay: " << initial_delay << " ps" << std::endl;

    {
        lab::Benchmark b("Buffer Insertion Optimization");
        res = opt.optimize_wire(WIRE_LEN);
    }

    std::cout << "[METRICS] Buffers Inserted: " << res.buffers << std::endl;
    std::cout << "[METRICS] Optimized Delay:  " << res.delay << " ps" << std::endl;
    std::cout << "[METRICS] Improvement:      " << (initial_delay - res.delay) / initial_delay * 100 << "%" << std::endl;

    lab::print_qor("Timing Optimization", 0, (size_t)res.delay);

    return 0;
}
