/**
 * EXPERIMENT: Monte Carlo Tree Search (MCTS)
 * 
 * GOAL: Implement the MCTS algorithm for decision-making in 
 * deterministic games (simplified Tic-Tac-Toe model).
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

struct MCTSNode {
    int visits = 0;
    float value = 0;
    std::vector<MCTSNode*> children;
    MCTSNode* parent;

    MCTSNode(MCTSNode* p = nullptr) : parent(p) {}

    float ucb1() const {
        if (visits == 0) return 1e18;
        return value / visits + 1.41f * std::sqrt(std::log((float)parent->visits) / visits);
    }
};

class MCTSSolver {
public:
    void solve(MCTSNode* root, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            // Selection
            MCTSNode* curr = root;
            while (!curr->children.empty()) {
                curr = *std::max_element(curr->children.begin(), curr->children.end(), 
                                        [](MCTSNode* a, MCTSNode* b) { return a->ucb1() < b->ucb1(); });
            }

            // Expansion
            for (int j = 0; j < 3; ++j) {
                curr->children.push_back(new MCTSNode(curr));
            }
            MCTSNode* next = curr->children[0];

            // Simulation (simplified: random win/loss)
            float reward = (rand() % 2 == 0) ? 1.0f : 0.0f;

            // Backpropagation
            while (next) {
                next->visits++;
                next->value += reward;
                next = next->parent;
            }
        }
    }
};

int main() {
    std::cout << "--- Monte Carlo Tree Search Laboratory ---" << std::endl;

    MCTSNode* root = new MCTSNode();
    MCTSSolver solver;

    {
        lab::Benchmark b("MCTS Search (5k iterations)");
        solver.solve(root, 5000);
    }

    std::cout << "[METRICS] Root Visits: " << root->visits << std::endl;
    std::cout << "[METRICS] Root Value Estimate: " << root->value / root->visits << std::endl;

    lab::print_qor("Search Memory", root->visits * sizeof(MCTSNode));

    return 0;
}
