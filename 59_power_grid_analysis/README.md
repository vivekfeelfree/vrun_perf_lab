# Module 59: Power Grid Analysis (IR Drop)

## 🎯 Goal
Calculate voltage drops across a power grid using an iterative Gauss-Seidel solver.

## 🧠 Key Concept
Power delivery networks (PDNs) experience voltage drops (IR drop) due to the resistance of the metal wires and the current consumed by the underlying logic. Analyzing this requires solving a large system of linear equations ($GV=I$), often using iterative methods like Gauss-Seidel for efficiency.

## 📊 Metrics to Watch
- **Worst-Case IR Drop:** The maximum voltage deviation from nominal VDD.
- **Solver Convergence:** Execution time relative to the number of iterations and grid size.
