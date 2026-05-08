# Module 91: Longest Path in a DAG

## 🎯 Goal
Find the longest path in a Directed Acyclic Graph (DAG) using topological sorting.

## 🧠 Key Concept
The Longest Path problem is NP-hard for general graphs, but for Directed Acyclic Graphs (DAGs), it can be solved efficiently in linear time. By processing nodes in topological order, we can iteratively update the longest distance to each node, which is a foundational algorithm for Static Timing Analysis (STA) in EDA.

## 📊 Metrics to Watch
- **Critical Distance:** Length of the identified longest path.
- **Traversal Speed:** Performance scaling with $V+E$.
