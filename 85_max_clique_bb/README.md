# Module 85: Maximum Clique (Branch & Bound)

## 🎯 Goal
Find the largest fully connected subgraph (clique) using a branch and bound search.

## 🧠 Key Concept
The Maximum Clique problem is a fundamental NP-hard problem in graph theory. This module implements a backtracking search with branch-and-bound pruning: the search space is pruned if the current clique plus the number of remaining nodes cannot possibly exceed the size of the best clique found so far.

## 📊 Metrics to Watch
- **Clique Size:** Number of nodes in the identified maximum clique.
- **Search Pruning:** Efficiency of the bound function in reducing states explored.
