# Module 43: Gate Sizing

## 🎯 Goal
Optimize a mapped netlist by choosing gate sizes to satisfy timing constraints while minimizing area.

## 🧠 Key Concept
Gate Sizing is a late-stage optimization where cells in a mapped netlist are replaced with different versions from the same library (e.g., swapping a 1x inverter for a 4x inverter). Larger gates are faster but consume more area and power.

## 📊 Metrics to Watch
- **Total Area:** Sum of all gate areas in the design.
- **Worst Case Delay:** Cumulative delay along the longest path.
