# Module 83: Boolean Satisfiability (WalkSAT)

## 🎯 Goal
Use a stochastic local search algorithm (WalkSAT) to find a satisfying assignment for a 3-SAT problem.

## 🧠 Key Concept
Unlike deterministic DPLL solvers, WalkSAT uses a stochastic approach. It randomly selects an unsatisfied clause and flips a variable within it. This "probabilistic walk" through the assignment space is remarkably effective for many large-scale SAT instances, though it is not complete (it cannot prove unsatisfiability).

## 📊 Metrics to Watch
- **Unsatisfied Count:** Number of clauses remaining to be satisfied.
- **Flip Throughput:** Number of variable flips processed per second.
