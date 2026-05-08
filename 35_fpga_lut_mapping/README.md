# Module 35: FPGA LUT Mapping

## 🎯 Goal
Implement a heuristic for mapping logic into K-input Look-Up Tables (LUTs).

## 🧠 Key Concept
FPGAs use LUTs to implement logic. A K-input LUT can implement any boolean function of K variables. Mapping involves covering the logic graph with "cuts" of size $\le K$. Depth-optimal mapping often uses the FlowMap algorithm.

## 📊 Metrics to Watch
- **LUT Count:** Total number of LUTs used.
- **Logic Depth:** Number of LUTs on the longest path.
