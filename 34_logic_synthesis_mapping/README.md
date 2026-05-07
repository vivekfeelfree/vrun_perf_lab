# Module 23: Technology Mapping (Dynamic Programming)

## 🎯 Core Problem
How do we map an abstract logic graph (AIG) to a set of physical gates (Standard Cells) to minimize either **Area** or **Delay**?

## 🧠 Technical Depth
### 1. The Tree Mapping Pattern
Because an AIG is a graph, we first break it into a forest of trees. For each tree, we can find the optimal mapping using **Dynamic Programming (DP)**.
- **Base Case:** The cost of an input pin is 0.
- **Recursive Step:** The cost of a node $N$ is:
  $Cost(N) = \min_{Match \in Library} \{ Cost(Match.Inputs) + Match.Cost \}$

### 2. Area vs. Delay (QoR Trade-offs)
- **Area-Oriented:** Minimize total gate count/size. (Sum of costs).
- **Delay-Oriented:** Minimize the Longest Path (Maximum of costs + gate delay).
This is a classic "Pareto Front" problem in EDA.

## 📊 Tracked Metrics
- **Time:** Wall-clock time to perform mapping on a 100K node graph.
- **QoR (Area):** Total area units of the mapped circuit.
- **QoR (Delay):** Critical path delay (arrival time at the root).
- **Efficiency:** Decisions per second.

## 🧪 Experiment
1.  Define a small library of gates (AND2, AND3, NAND2).
2.  Implement a DP-based mapper for an AIG tree.
3.  Compare the results of Area-Mapping vs. Delay-Mapping.

## 🎛 Experimental Controls
- **Library Complexity:** Number of gates available for matching.
- **Tree Depth:** Impact of logic depth on DP execution time.
