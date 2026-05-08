# Module 51: Floorplanning (Simulated Annealing)

## 🎯 Goal
Optimize the placement of macro blocks to minimize a weighted sum of Total Area and Wirelength.

## 🧠 Key Concept
Simulated Annealing is a probabilistic technique for approximating the global optimum of a given function. In floorplanning, we randomly move or swap blocks and accept "bad" moves with a probability that decreases over time (the "temperature"), allowing the algorithm to escape local minima.

## 📊 Metrics to Watch
- **Total Area:** Bounding box of all blocks.
- **Cost Convergence:** How the cost decreases across iterations.
