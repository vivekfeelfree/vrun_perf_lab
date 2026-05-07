/**
 * EXPERIMENT: SAT Solver Efficiency (Unit Propagation)
 * 
 * GOAL: Measure the performance impact of Unit Propagation (BCP) 
 * on the SAT search space.
 */

#include "../include/harness.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

typedef int lit; // Positive for Var, Negative for NOT Var

struct Clause {
    std::vector<lit> lits;
};

class SATSolver {
    int num_vars;
    std::vector<Clause> clauses;
    std::vector<int> assignment; // 0: Undecided, 1: True, -1: False

    // Metrics
    size_t decisions = 0;
    size_t propagations = 0;

public:
    SATSolver(int vars) : num_vars(vars), assignment(vars + 1, 0) {}

    void add_clause(const std::vector<lit>& l) {
        clauses.push_back({l});
    }

    // Check if a literal is satisfied by current assignment
    int lit_val(lit l) {
        int var = std::abs(l);
        if (assignment[var] == 0) return 0;
        return (l > 0) ? assignment[var] : -assignment[var];
    }

    /**
     * UNIT PROPAGATION (BCP)
     * Returns false if a conflict is found.
     */
    bool propagate() {
        bool changed = true;
        while (changed) {
            changed = false;
            for (const auto& clause : clauses) {
                int satisfied = 0;
                int unassigned_count = 0;
                lit last_unassigned = 0;

                for (lit l : clause.lits) {
                    int val = lit_val(l);
                    if (val == 1) { satisfied = 1; break; }
                    if (val == 0) { unassigned_count++; last_unassigned = l; }
                }

                if (satisfied) continue;

                if (unassigned_count == 0) return false; // CONFLICT!

                if (unassigned_count == 1) {
                    // We found a unit clause! Assign it.
                    int var = std::abs(last_unassigned);
                    assignment[var] = (last_unassigned > 0) ? 1 : -1;
                    propagations++;
                    changed = true;
                }
            }
        }
        return true;
    }

    /**
     * RECURSIVE SOLVER
     * @param use_bcp: Toggle for optimization
     */
    bool solve(int var_idx, bool use_bcp) {
        if (use_bcp && !propagate()) return false;

        // Find next unassigned variable
        while (var_idx <= num_vars && assignment[var_idx] != 0) var_idx++;
        
        if (var_idx > num_vars) return true; // All assigned!

        decisions++;

        // Try True
        assignment[var_idx] = 1;
        // Optimization: In a real solver, we'd save the state for backtracking
        // Here we use a simple copy-based approach for the lab's clarity
        auto backup = assignment;
        if (solve(var_idx + 1, use_bcp)) return true;
        
        // Backtrack and Try False
        assignment = backup;
        assignment[var_idx] = -1;
        if (solve(var_idx + 1, use_bcp)) return true;

        assignment[var_idx] = 0; // Final backtrack
        return false;
    }

    void reset() {
        std::fill(assignment.begin(), assignment.end(), 0);
        decisions = 0;
        propagations = 0;
    }

    void report_metrics(const char* label) {
        std::cout << "[METRICS] " << label << ":" << std::endl;
        std::cout << "   - Decisions:    " << decisions << std::endl;
        std::cout << "   - Propagations: " << propagations << std::endl;
    }
};

/**
 * PIGEONHOLE PRINCIPLE (PHP)
 * Attempting to put (N+1) pigeons into N holes.
 * This is always UNSATISFIABLE.
 */
void setup_php(SATSolver& solver, int pigeons, int holes) {
    auto var = [&](int p, int h) { return p * holes + h + 1; };

    // 1. Every pigeon must be in at least one hole
    for (int p = 0; p < pigeons; ++p) {
        std::vector<lit> clause;
        for (int h = 0; h < holes; ++h) clause.push_back(var(p, h));
        solver.add_clause(clause);
    }

    // 2. No two pigeons in the same hole
    for (int h = 0; h < holes; ++h) {
        for (int p1 = 0; p1 < pigeons; ++p1) {
            for (int p2 = p1 + 1; p2 < pigeons; ++p2) {
                solver.add_clause({-var(p1, h), -var(p2, h)});
            }
        }
    }
}

int main() {
    int P = 4, H = 3;
    std::cout << "--- SAT Solver Laboratory (Pigeonhole PHP-" << P << "-" << H << ") ---" << std::endl;

    SATSolver solver(P * H);
    setup_php(solver, P, H);

    {
        solver.reset();
        lab::Benchmark b("Naive Backtracking");
        bool result = solver.solve(1, false);
        lab::escape(&result);
        solver.report_metrics("Naive");
    }

    {
        solver.reset();
        lab::Benchmark b("Backtracking + Unit Prop");
        bool result = solver.solve(1, true);
        lab::escape(&result);
        solver.report_metrics("Optimized");
    }

    return 0;
}
