# Module 19: Cache-Oblivious Algorithms (Matrix Transpose)

## The Core Problem: Tiled Cache Optimization
When transposing a large matrix, the standard "Naive" nested loop causes many cache misses:
```cpp
for (i...) for (j...) B[j][i] = A[i][j];
```
One of the accesses (either read or write) will be "strided," meaning it jumps across memory lines, causing a miss every single time.

## 1. The Tiled Solution (Cache-Aware)
You can break the matrix into small blocks (tiles) that fit in your L1 cache.
**Problem:** You need to know your L1 cache size (e.g., 32KB) to pick the best tile size.

## 2. The Cache-Oblivious Solution
By using a **Recursive Divide and Conquer** strategy, the algorithm automatically "tiles" itself at every level of the memory hierarchy (L1, L2, L3, and even Disk/RAM).
1.  If the matrix is small, transpose it.
2.  If the matrix is large, split it into 4 quadrants and recurse.

No matter what the cache size is, at some point the recursion will hit a sub-problem that fits perfectly in that cache.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **Naive Transpose.**
2.  **Recursive Cache-Oblivious Transpose.**

## 🎛 Experimental Controls
- **Matrix Size:** Start small and grow until it exceeds the L3 cache.
- **Recursion Threshold:** Find the point where the overhead of recursion outweighs the cache benefits.
