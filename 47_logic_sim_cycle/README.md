# Module 47: Cycle-Based Simulation

## 🎯 Goal
Demonstrate high-throughput simulation using bit-parallel (SWAR) techniques to process 64 patterns at once.

## 🧠 Key Concept
Cycle-based simulation evaluates the entire circuit at fixed time intervals (clock cycles). Bit-parallel simulation leverages 64-bit registers to simulate 64 independent test vectors simultaneously using standard bitwise logic instructions.

## 📊 Metrics to Watch
- **Boolean Throughput:** Total number of gate evaluations per second.
- **Cache Locality:** Effectiveness of processing gates in topological order.
