# Module 89: Minimum Vertex Cover (Approx)

## 🎯 Goal
Implement the 2-approximation greedy algorithm for minimum vertex cover and measure its result quality.

## 🧠 Key Concept
The Minimum Vertex Cover problem is NP-hard. A simple 2-approximation algorithm works by repeatedly picking an uncovered edge and adding both its endpoints to the cover. This guarantees the cover size is at most twice the optimal size, providing a fast and reliable heuristic for large-scale graph problems.

## 📊 Metrics to Watch
- **Cover Size:** Total nodes in the vertex cover.
- **Traversal Speed:** Linear performance relative to edge count.
