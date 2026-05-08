# Module 61: Detailed Routing

## 🎯 Goal
Implement A* search on a multi-layer grid with variable costs for vias and preferred routing directions.

## 🧠 Key Concept
Detailed routing is the final step in the routing flow, where actual metal segments are assigned to tracks on specific layers. It must adhere to strict Design Rule Checks (DRC) and minimize costs associated with switching layers (vias) and deviating from a layer's preferred routing direction (e.g., horizontal on M2, vertical on M3).

## 📊 Metrics to Watch
- **Route Cost:** Weighted sum of wirelength and via count.
- **Search Efficiency:** Number of 3D grid cells explored.
