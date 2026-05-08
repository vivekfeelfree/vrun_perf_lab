# Module 94: Sudoku Solver (Backtracking)

## 🎯 Goal
Solve a 9x9 Sudoku puzzle using recursive backtracking with constraint propagation.

## 🧠 Key Concept
Sudoku is a constraint satisfaction problem that can be represented as an NP-complete graph coloring problem. This module uses backtracking search—systematically trying numbers and recursing, but "backtracking" immediately when a constraint violation is detected—to find the unique solution.

## 📊 Metrics to Watch
- **Solve Time:** Nanoseconds taken to fill the grid.
- **Search Depth:** Maximum recursion level reached.
