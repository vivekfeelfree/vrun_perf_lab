# Module 23: Min-Cost Max-Flow (Successive Shortest Path)

## 🎯 Goal
Implement Min-Cost Max-Flow (MCMF) using the Successive Shortest Path algorithm.

## 🧠 Key Concept
MCMF finds a flow that is both maximum in volume and minimum in total cost. The Successive Shortest Path algorithm repeatedly finds the shortest path in the residual graph using SPFA (or Bellman-Ford) and augments flow along it.

## 📊 Metrics to Watch
- **Total Cost:** The primary QoR metric.
- **Execution Time:** MCMF is significantly more computationally expensive than standard Max Flow.
