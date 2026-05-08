# Module 60: Parasitic Extraction (Elmore Delay)

## 🎯 Goal
Calculate the Elmore delay for an RC tree network representing a routed net.

## 🧠 Key Concept
Parasitic extraction estimates the resistance (R) and capacitance (C) of interconnects. The Elmore delay is a first-order approximation of the signal delay through an RC tree, calculated as the sum of $R_i \cdot C_{subtree\_i}$ for all branches on the path from source to sink.

## 📊 Metrics to Watch
- **Delay Accuracy:** Comparison of Elmore delay against more complex models.
- **Computation Latency:** Efficiency of traversing large RC trees.
