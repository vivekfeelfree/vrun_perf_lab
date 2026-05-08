# Module 90: Hamiltonian Path (Backtracking)

## 🎯 Goal
Find a path that visits every vertex exactly once using an exhaustive backtracking search.

## 🧠 Key Concept
A Hamiltonian Path is a path in an undirected or directed graph that visits each vertex exactly once. Determining its existence is NP-complete. Backtracking explores all possible paths, pruning branches only when they lead to dead ends (no remaining neighbors to visit).

## 📊 Metrics to Watch
- **Exploration Depth:** Number of recursion levels reached.
- **Search Latency:** Time taken to identify a path or exhaust the space.
