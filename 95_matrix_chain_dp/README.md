# Module 95: Matrix Chain Multiplication (DP)

## 🎯 Goal
Find the optimal parenthesization of a matrix chain to minimize the total number of scalar multiplications.

## 🧠 Key Concept
Matrix multiplication is associative, but the order of operations significantly impacts the total number of multiplications needed. For example, multiplying $(A \times B) \times C$ may require much more work than $A \times (B \times C)$. This module uses dynamic programming to solve the problem in $O(N^3)$ time by computing the optimal cost for every possible sub-chain.

## 📊 Metrics to Watch
- **Optimal Cost:** Minimum scalar multiplications required.
- **DP Efficiency:** Execution time scaling with chain length.
