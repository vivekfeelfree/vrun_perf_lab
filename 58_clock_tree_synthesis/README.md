# Module 58: Clock Tree Synthesis (H-Tree)

## 🎯 Goal
Construct a balanced H-tree to distribute a clock signal with minimal skew to all registers.

## 🧠 Key Concept
Clock Tree Synthesis (CTS) aims to deliver the clock signal to all registers at exactly the same time. The H-tree is a recursive geometric pattern that ensures every leaf (sink) is at the same wire distance from the source (the root), effectively eliminating geometric skew.

## 📊 Metrics to Watch
- **Wirelength:** Total metal used for the clock network.
- **Sink Count:** Number of clock sinks served.
