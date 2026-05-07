# Module 27: Disjoint Set Union (DSU)

## 🎯 Goal
Measure the efficiency of the DSU data structure with Path Compression and Union by Rank.

## 🧠 Key Concept
DSU manages a partition of elements into disjoint sets. It supports two main operations: `find` (determine which set an element belongs to) and `unite` (merge two sets). With optimizations, these operations take nearly constant time.

## 📊 Metrics to Watch
- **Amortized Time:** Observation of near $O(1)$ performance.
- **Path Compression Impact:** Significant reduction in tree depth over time.
