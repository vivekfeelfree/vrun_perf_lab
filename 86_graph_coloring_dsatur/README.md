# Module 86: Graph Coloring (DSATUR)

## 🎯 Goal
Use the Degree of Saturation (DSATUR) heuristic to color a graph with a near-minimum number of colors.

## 🧠 Key Concept
Graph coloring is essential for resource allocation (like register allocation in compilers or wavelength assignment in optical networks). DSATUR is a powerful heuristic that prioritizes coloring nodes with the most "saturated" neighborhood (i.e., those whose neighbors already have the most diverse set of colors).

## 📊 Metrics to Watch
- **Chromatic Number:** Total colors used (approximation of minimum).
- **Selection Efficiency:** Performance of the max-saturation node finding step.
