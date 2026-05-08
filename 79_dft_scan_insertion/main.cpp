/**
 * EXPERIMENT: DFT Scan Chain Insertion
 * 
 * GOAL: Transform standard flip-flops into scan-flops and measure 
 * the impact on area and testability.
 */

#include "../include/harness.hpp"
#include <vector>

struct Flop {
    int id;
    bool is_scan;
};

class ScanManager {
    std::vector<Flop> flops;

public:
    void add_flops(int n) {
        for (int i = 0; i < n; ++i) flops.push_back({i, false});
    }

    void insert_scan() {
        for (auto& f : flops) f.is_scan = true;
    }

    float estimate_area_overhead() {
        // A scan-flop is typically 20-30% larger than a standard flop
        return flops.size() * 0.25f;
    }
};

int main() {
    int N = 5000;
    std::cout << "--- DFT Scan Insertion Laboratory (" << N << " flops) ---" << std::endl;

    ScanManager sm;
    sm.add_flops(N);

    {
        lab::Benchmark b("Scan Chain Insertion");
        sm.insert_scan();
    }

    float overhead = sm.estimate_area_overhead();
    std::cout << "[METRICS] Area Overhead: " << overhead << " units" << std::endl;
    std::cout << "[METRICS] Testability (Controllability): 100%" << std::endl;

    lab::print_qor("DFT Metrics", (size_t)overhead, N);

    return 0;
}
