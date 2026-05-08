# Module 77: Glitch Analysis

## 🎯 Goal
Identify potential static hazards (glitches) in combinational logic due to unequal path delays.

## 🧠 Key Concept
A glitch is a temporary unwanted transition at the output of a circuit before it settles to its intended steady-state value. This usually happens in combinational logic when the inputs to a gate arrive at different times due to varying path lengths. While glitches don't always affect logic correctness, they consume extra power.

## 📊 Metrics to Watch
- **Hazard Count:** Number of gates at risk of glitching.
- **Skew Analysis:** Maximum delay difference between gate inputs.
