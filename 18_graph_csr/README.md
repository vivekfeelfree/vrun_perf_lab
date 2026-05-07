# Module 18: Graph Representations (CSR vs. Adjacency Lists)

## The Core Problem: Millions of Edges
In EDA tools (like Logic Synthesis), we represent a circuit as a Directed Acyclic Graph (DAG).
A typical chip has 100M+ edges.

### The "Naive" Adjacency List
```cpp
vector<vector<int>> adj;
```
**Problem:** This is an "Array of Arrays."
1.  **Memory overhead:** Each inner `vector` has its own capacity, size, and heap pointer.
2.  **Pointer Chasing:** Iterating through all edges requires jumping to a new heap location for every node.

## 1. The CSR Solution (Compressed Sparse Row)
CSR flattens the entire graph into just **Two Arrays**:
1.  **`edges` Array:** All neighbor IDs for all nodes, packed contiguously.
2.  **`offsets` Array:** The starting index in the `edges` array for each node.

### Example:
- Node 0 has neighbors {1, 2}
- Node 1 has neighbor {3}
- `edges` = `[1, 2, 3]`
- `offsets` = `[0, 2, 3]` (Node 0 starts at 0, Node 1 starts at 2).

## 2. Advantages for EDA
1.  **Cache Locality:** All edges for a node are guaranteed to be side-by-side in memory.
2.  **Compact:** Zero waste from vector capacities.
3.  **Parallel Friendly:** Because the graph is just two flat arrays, it is very easy to partition for multi-threading.

## 3. The Experiment
In `main.cpp`, we will build a large random graph and measure the time to perform a "BFS" or a "Neighbor Sum."
1.  **Naive:** `std::vector<std::vector<int>>`.
2.  **Optimized:** `lab::CSRGraph`.

## 🎛 Experimental Controls
- **Graph Sparsity:** How does performance change if every node has 2 neighbors vs 100 neighbors?
- **Traversal Depth:** Measure the time to traverse a 10-level deep logic path.
