# Module 82: Hypergraph Partitioning (FM)

## 🎯 Goal
Implement the Fiduccia-Mattheyses (FM) heuristic to minimize the cut-size of a hypergraph.

## 🧠 Key Concept
Hypergraph partitioning is a foundational problem in EDA netlist placement and logic synthesis. The FM algorithm is an iterative move-based heuristic that calculates the "gain" for moving each node between partitions and executes the best sequence of moves, even if some moves temporarily increase the cut-size, to find a better global solution.

## 📊 Metrics to Watch
- **Hyperedge Cut:** Number of hyperedges that span both partitions.
- **Pass Convergence:** Improvement in cut-size per iteration.
