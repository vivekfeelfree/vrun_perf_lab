# Module 38: Observability Don't Cares (ODC)

## 🎯 Goal
Identify logic nodes that are "don't cares" because their value doesn't propagate to any primary output.

## 🧠 Key Concept
A node is an ODC if flipping its value has no effect on the primary outputs for a given set of input patterns. Identifying ODCs allows for pruning redundant logic and reducing power consumption.

## 📊 Metrics to Watch
- **ODC Count:** Number of nodes that can be simplified.
- **Simulation Coverage:** Number of patterns used to verify observability.
