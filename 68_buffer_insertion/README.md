# Module 68: Timing Closure (Buffer Insertion)

## 🎯 Goal
Reduce wire delay on critical paths by inserting buffers at optimal intervals to break up long RC chains.

## 🧠 Key Concept
The delay of a metal wire increases quadratically with its length ($0.5 RCL^2$). By inserting buffers (repeaters), the wire is divided into shorter segments, each with a linear contribution to the overall delay. This is a critical technique for achieving timing closure on long global nets.

## 📊 Metrics to Watch
- **Delay Reduction:** Percentage improvement in path timing.
- **Buffer Overhead:** Additional area and power consumed by inserted buffers.
