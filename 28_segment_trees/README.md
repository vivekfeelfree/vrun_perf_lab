# Module 28: Segment Trees

## 🎯 Goal
Compare $O(\log N)$ range queries and updates in a Segment Tree against $O(N)$ linear scans.

## 🧠 Key Concept
A Segment Tree is a tree data structure used for storing information about intervals or segments. It allows querying which of the stored segments contain a given point, or finding the sum/min/max of a range in $O(\log N)$ time.

## 📊 Metrics to Watch
- **Query Latency:** Nanoseconds per range sum query.
- **Memory Overhead:** Segment trees typically use $4N$ memory.
