# Module 30: Minimum Spanning Tree (Kruskal's)

## 🎯 Goal
Implement Kruskal's algorithm for finding the Minimum Spanning Tree (MST) using the DSU data structure.

## 🧠 Key Concept
Kruskal's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. It sorts all edges by weight and uses DSU to efficiently detect and avoid cycles while building the tree.

## 📊 Metrics to Watch
- **Sorting Time:** Often the bottleneck of Kruskal's ($O(E \log E)$).
- **MST Weight:** Total weight of the minimum spanning tree.
