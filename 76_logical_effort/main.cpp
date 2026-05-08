/**
 * EXPERIMENT: Logical Effort Path Optimization
 * 
 * GOAL: Use the Method of Logical Effort to determine the optimal 
 * number of stages and gate sizing for a multi-stage logic path.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

class LogicalEffortOptimizer {
public:
    struct PathResult { int stages; float total_delay; };

    PathResult optimize(float path_effort, int initial_stages) {
        // Delay D = N * (G*H*B)^(1/N) + P
        // For simplicity: G*H*B is given as path_effort
        float best_delay = 1e18;
        int best_n = initial_stages;

        for (int n = 1; n <= 10; ++n) {
            float stage_effort = std::pow(path_effort, 1.0f / n);
            float delay = n * stage_effort + n * 1.0f; // Assuming parasitic delay p=1 per stage
            if (delay < best_delay) {
                best_delay = delay;
                best_n = n;
            }
        }
        return {best_n, best_delay};
    }
};

int main() {
    std::cout << "--- Logical Effort Path Optimization Laboratory ---" << std::endl;

    LogicalEffortOptimizer opt;
    float PATH_EFFORT = 125.0f; // e.g., a path driving a large load

    LogicalEffortOptimizer::PathResult res;
    {
        lab::Benchmark b("Path Delay Optimization");
        res = opt.optimize(PATH_EFFORT, 1);
    }

    std::cout << "[METRICS] Optimal Number of Stages: " << res.stages << std::endl;
    std::cout << "[METRICS] Minimized Path Delay:     " << res.total_delay << " units" << std::endl;

    lab::print_qor("Optimization effort", 0, res.stages);

    return 0;
}
