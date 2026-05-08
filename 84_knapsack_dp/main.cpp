/**
 * EXPERIMENT: 0/1 Knapsack Problem (Dynamic Programming)
 * 
 * GOAL: Solve the 0/1 Knapsack problem using dynamic programming 
 * and measure time and memory scaling.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Item {
    int weight;
    int value;
};

class KnapsackSolver {
public:
    int solve(int capacity, const std::vector<Item>& items) {
        int n = items.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int w = 0; w <= capacity; ++w) {
                if (items[i - 1].weight <= w) {
                    dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][capacity];
    }
};

int main() {
    int N = 500;
    int W = 1000;
    std::cout << "--- 0/1 Knapsack (DP) Laboratory (" << N << " items, " << W << " capacity) ---" << std::endl;

    std::vector<Item> items;
    for (int i = 0; i < N; ++i) {
        items.push_back({rand() % 50 + 1, rand() % 100 + 1});
    }

    KnapsackSolver solver;
    int max_val = 0;
    {
        lab::Benchmark b("Knapsack DP Solver");
        max_val = solver.solve(W, items);
    }

    std::cout << "[METRICS] Maximum Value: " << max_val << std::endl;
    lab::print_qor("DP Table", N * W * sizeof(int), max_val);

    return 0;
}
