# Module 56: Steiner Tree Construction

## 🎯 Goal
Use an MST-based heuristic to approximate the shortest rectilinear tree (RSMT) connecting a set of pins.

## 🧠 Key Concept
The Rectilinear Steiner Minimum Tree (RSMT) is the shortest tree connecting a set of points using only horizontal and vertical segments. While finding the exact RSMT is NP-hard, the Minimum Spanning Tree (MST) in the Manhattan space provides a 1.5-approximation, which is widely used for wirelength estimation.

## 📊 Metrics to Watch
- **Total Wirelength:** Cumulative length of all tree segments.
- **Computation Time:** Growth as the number of pins increases.
