# Module 75: Thermal Analysis (2D Diffusion)

## 🎯 Goal
Simulate temperature distribution across a chip using a 2D finite-difference heat diffusion model.

## 🧠 Key Concept
Modern high-performance chips generate significant heat. Thermal analysis involves solving the heat equation $\frac{\partial T}{\partial t} = \alpha \nabla^2 T + P$ to identify "hot spots" that can degrade performance or lead to permanent failure. This is often solved using iterative spatial grids.

## 📊 Metrics to Watch
- **Peak Temperature:** The highest junction temperature on the die.
- **Gradient Density:** How quickly temperature varies across the chip area.
