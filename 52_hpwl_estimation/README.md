# Module 52: HPWL Estimation

## 🎯 Goal
Efficiently estimate total wirelength for a set of nets during placement using the HPWL metric.

## 🧠 Key Concept
The Half-Perimeter Wirelength (HPWL) is the most common metric for estimating wirelength during placement. For a net, it is calculated as the half-perimeter of the bounding box enclosing all its pins: $(x_{max} - x_{min}) + (y_{max} - y_{min})$.

## 📊 Metrics to Watch
- **Computation Throughput:** Nets processed per second.
- **Memory Footprint:** Efficiency of storing pin locations and net lists.
