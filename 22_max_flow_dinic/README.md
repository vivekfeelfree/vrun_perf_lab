# Module 22: Maximum Flow (Dinic's Algorithm)

## 🎯 Goal
Implement and benchmark Dinic's algorithm for finding the maximum flow in a network.

## 🧠 Key Concept
Dinic's algorithm improves on Edmonds-Karp by using **level graphs** and **blocking flows**. It uses BFS to build a level graph and then multiple DFS passes to find blocking flows within that level graph.

## 📊 Metrics to Watch
- **Execution Time:** Should scale much better than Edmonds-Karp on complex networks.
- **Memory Footprint:** Adjacency list representation with residual capacities.
