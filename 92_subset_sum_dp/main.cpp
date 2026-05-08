/**
 * EXPERIMENT: Subset Sum Problem (Dynamic Programming)
 * 
 * GOAL: Determine if a subset of integers sums to a target value 
 * using an efficient DP approach.
 */

#include "../include/harness.hpp"
#include <vector>

class SubsetSumSolver {
public:
    bool solve(const std::vector<int>& nums, int target) {
        int n = nums.size();
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

        for (int i = 0; i <= n; ++i) dp[i][0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j) {
                if (nums[i - 1] <= j) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][target];
    }
};

int main() {
    int TARGET = 2000;
    std::cout << "--- Subset Sum (DP) Laboratory ---" << std::endl;

    std::vector<int> nums;
    for (int i = 0; i < 100; ++i) nums.push_back(rand() % 100 + 1);

    SubsetSumSolver solver;
    bool found = false;
    {
        lab::Benchmark b("Subset Sum DP Search");
        found = solver.solve(nums, TARGET);
    }

    std::cout << "[METRICS] Target Found: " << (found ? "YES" : "NO") << std::endl;
    lab::print_qor("DP State Space", nums.size() * TARGET * sizeof(bool));

    return 0;
}
