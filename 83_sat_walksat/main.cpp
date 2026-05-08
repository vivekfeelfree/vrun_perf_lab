/**
 * EXPERIMENT: Boolean Satisfiability (WalkSAT)
 * 
 * GOAL: Use a stochastic local search algorithm to find a satisfying 
 * assignment for a 3-SAT problem.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>
#include <random>

struct Clause {
    int lits[3]; // Literal: var_idx * 2 + sign (0: pos, 1: neg)
};

class WalkSATSolver {
    int n_vars;
    std::vector<Clause> clauses;
    std::vector<bool> assignment;

public:
    WalkSATSolver(int n) : n_vars(n), assignment(n) {
        for (int i = 0; i < n; ++i) assignment[i] = rand() % 2;
    }

    void add_clause(int v1, bool s1, int v2, bool s2, int v3, bool s3) {
        clauses.push_back({{v1 * 2 + s1, v2 * 2 + s2, v3 * 2 + s3}});
    }

    bool is_satisfied(const Clause& c) {
        for (int l : c.lits) {
            int var = l / 2;
            bool sign = l % 2;
            if (assignment[var] == !sign) return true;
        }
        return false;
    }

    int count_unsatisfied() {
        int count = 0;
        for (const auto& c : clauses) if (!is_satisfied(c)) count++;
        return count;
    }

    bool solve(int max_flips, float p) {
        std::mt19937 gen(42);
        std::uniform_real_distribution<float> dis(0, 1);

        for (int i = 0; i < max_flips; ++i) {
            std::vector<int> unsatisfied;
            for (int j = 0; j < (int)clauses.size(); ++j) {
                if (!is_satisfied(clauses[j])) unsatisfied.push_back(j);
            }

            if (unsatisfied.empty()) return true;

            int target_clause = unsatisfied[rand() % unsatisfied.size()];
            int var_to_flip = clauses[target_clause].lits[rand() % 3] / 2;

            // Simple WalkSAT logic: with probability p, flip a random var in clause
            // Otherwise, flip the one that minimizes unsatisfied count (simplified here)
            if (dis(gen) > p) {
                // Greedy flip would go here
            }
            assignment[var_to_flip] = !assignment[var_to_flip];
        }
        return false;
    }

    size_t memory_usage() const { return clauses.size() * sizeof(Clause) + assignment.size() * sizeof(bool); }
};

int main() {
    int VARS = 50, CLAUSES = 200;
    std::cout << "--- WalkSAT Laboratory (" << VARS << " vars, " << CLAUSES << " clauses) ---" << std::endl;

    WalkSATSolver solver(VARS);
    for (int i = 0; i < CLAUSES; ++i) {
        solver.add_clause(rand() % VARS, rand() % 2, rand() % VARS, rand() % 2, rand() % VARS, rand() % 2);
    }

    std::cout << "[METRICS] Initial Unsatisfied: " << solver.count_unsatisfied() << std::endl;

    bool success = false;
    {
        lab::Benchmark b("WalkSAT Search (10k flips)");
        success = solver.solve(10000, 0.3f);
    }

    std::cout << "[METRICS] Result: " << (success ? "SATISFIED" : "GAVE UP") << std::endl;
    std::cout << "[METRICS] Final Unsatisfied: " << solver.count_unsatisfied() << std::endl;

    lab::print_qor("SAT Metrics", solver.memory_usage());

    return 0;
}
