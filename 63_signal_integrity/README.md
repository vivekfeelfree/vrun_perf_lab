# Module 63: Signal Integrity (Crosstalk)

## 🎯 Goal
Estimate coupling capacitance and crosstalk voltage between adjacent parallel wires.

## 🧠 Key Concept
As technology nodes shrink, wires become closer together, increasing the **coupling capacitance** between them. When a signal switches on one wire (the aggressor), it can induce a voltage spike on an adjacent wire (the victim) through crosstalk, potentially causing logic errors or timing violations.

## 📊 Metrics to Watch
- **Maximum Crosstalk:** The worst-case noise induced on any wire.
- **Analysis Latency:** Time to analyze all pairs of potentially coupled wires.
