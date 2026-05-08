# Module 37: Combinational Equivalence Checking (CEC)

## 🎯 Goal
Identify non-equivalent points between two logic designs using a miter and random simulation.

## 🧠 Key Concept
CEC verifies that two circuits implement the same function. A **miter** is constructed by XORing the outputs of the two circuits. If any input combination makes the XOR output '1', the circuits are non-equivalent.

## 📊 Metrics to Watch
- **Bug Detection:** Success in finding mismatching patterns.
- **Simulation Throughput:** Patterns processed per second.
