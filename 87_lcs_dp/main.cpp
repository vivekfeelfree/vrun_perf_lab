/**
 * EXPERIMENT: Longest Common Subsequence (LCS) via DP
 * 
 * GOAL: Use dynamic programming to find the longest common 
 * subsequence between two strings.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>
#include <algorithm>

class LCSSolver {
public:
    int solve(const std::string& s1, const std::string& s2) {
        int n = s1.size();
        int m = s2.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
};

int main() {
    std::string s1 = "ABCBDAB", s2 = "BDCABA";
    std::cout << "--- LCS (DP) Laboratory ---" << std::endl;

    LCSSolver solver;
    int length = 0;
    {
        lab::Benchmark b("LCS DP Solver");
        length = solver.solve(s1, s2);
    }

    std::cout << "[METRICS] LCS Length: " << length << std::endl;
    lab::print_qor("DP Table", s1.size() * s2.size() * sizeof(int), length);

    return 0;
}
