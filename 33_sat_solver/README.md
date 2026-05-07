# Module 22: SAT Solvers & Unit Propagation (BCP)

## The Core Problem: Searching the Boolean Space
Given a boolean formula in **CNF (Conjunctive Normal Form)**, find an assignment of variables (True/False) that makes the whole formula True.
- Naive Search: $O(2^n)$. For 100 variables, this is $10^{30}$ combinations.

## 1. Boolean Constraint Propagation (BCP)
Most of the "search" in a SAT solver isn't actually searching; it's **Inference**.
If we have a clause `(A OR B OR C)` and we know `A=False` and `B=False`, then `C` **must** be True. This is a **Unit Clause**.

**Unit Propagation** is the process of repeatedly finding unit clauses and assigning them until no more can be found. In production solvers, BCP takes ~80-90% of the execution time.

## 2. Metrics for Deep Comparison
In this experiment, we compare **Pure Backtracking** against **Backtracking + Unit Propagation**.
- **Execution Time (ns):** Total time to find a solution or prove unsatisfiability.
- **Decision Count:** How many times the solver had to "guess" a variable's value.
- **Propagation Count:** How many variables were inferred automatically.
- **Speedup Ratio:** The impact of BCP on the search efficiency.

## 3. The Experiment
We will solve a **Pigeonhole Principle** instance (e.g., trying to put 4 pigeons in 3 holes). This is a classic "hard" SAT problem that causes naive solvers to struggle.

## 🎛 Experimental Controls
- **Problem Scale:** Increase the number of variables and observe the exponential vs. sub-exponential growth in time.
- **Clause Density:** See how "tight" constraints affect propagation efficiency.
