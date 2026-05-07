# Module 24: Bipartite Matching (Hopcroft-Karp)

## 🎯 Goal
Implement the Hopcroft-Karp algorithm for maximum bipartite matching.

## 🧠 Key Concept
Hopcroft-Karp is a specialized algorithm for bipartite graphs that runs in $O(E \sqrt{V})$ time. It works by finding multiple augmenting paths in each BFS/DFS phase, similar to Dinic's algorithm.

## 📊 Metrics to Watch
- **Matching Size:** Number of matched pairs.
- **Scaling:** Performance on large graphs (e.g., 5000x5000 nodes).
