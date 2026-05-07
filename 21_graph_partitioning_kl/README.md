# Module 20: Kernighan-Lin (K-L) Graph Partitioning

## 🎯 Core Problem
Given a graph with $2n$ nodes, how do we divide it into two equal-sized partitions $A$ and $B$ such that the number of edges crossing between them (the "cut-set") is minimized?

## 🧠 Technical Depth
### 1. The Heuristic Strategy
Since finding the absolute minimum cut is NP-hard, the K-L algorithm uses a greedy iterative approach:
- **Gain Calculation:** For each pair of nodes $(a, b)$ where $a \in A$ and $b \in B$, calculate how much the cut-set would decrease if we swapped them.
  $Gain(a, b) = D_a + D_b - 2c_{ab}$
  where $D$ is the difference between external and internal edge costs.
- **Iterative Swapping:** Swap the pair with the maximum gain, even if the gain is negative (to escape local minima).
- **Locking:** Once a node is swapped, it is "locked" for the remainder of the pass to prevent infinite loops.

### 2. Time Complexity
- A single pass takes $O(n^2 \log n)$ or $O(n^3)$ depending on the implementation of the gain sorting.
- We will focus on the **gain-update efficiency** in C++.

## 📊 Tracked Metrics
- **Temporal:** Wall-clock time to converge on a stable partition.
- **QoR (Cut-set Size):** Initial random cut-set vs. Final optimized cut-set.
- **Efficiency:** Gain per swap iteration.

## 🧪 Experiment
1.  Generate a random graph with 1,000 nodes and 5,000 edges.
2.  Perform an initial random 50/50 split.
3.  Run the K-L algorithm and measure the reduction in cut-set size.

## 🎛 Experimental Controls
- **Graph Density:** How does K-L perform on sparse vs. dense graphs?
- **Initial Partitioning:** Does the starting state significantly affect the final result?
