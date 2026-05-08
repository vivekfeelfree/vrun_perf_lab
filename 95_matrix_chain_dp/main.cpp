/**
 * EXPERIMENT: Matrix Chain Multiplication (Dynamic Programming)
 * 
 * GOAL: Find the optimal parenthesization of a matrix chain 
 * to minimize the total number of scalar multiplications.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

class MatrixChainSolver {
public:
    int solve(const std::vector<int>& dims) {
        int n = dims.size() - 1;
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = 1e9;
                for (int k = i; k < j; ++k) {
                    int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                    if (cost < dp[i][j]) dp[i][j] = cost;
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    std::cout << "--- Matrix Chain Multiplication (DP) Laboratory ---" << std::endl;

    std::vector<int> dims = {10, 30, 5, 60, 10, 20}; // A:10x30, B:30x5, C:5x60, ...
    MatrixChainSolver solver;
    int min_cost = 0;
    {
        lab::Benchmark b("Matrix Chain Optimization");
        min_cost = solver.solve(dims);
    }

    std::cout << "[METRICS] Minimum Scalar Multiplications: " << min_cost << std::endl;
    lab::print_qor("DP Footprint", dims.size() * dims.size() * sizeof(int), min_cost);

    return 0;
}
