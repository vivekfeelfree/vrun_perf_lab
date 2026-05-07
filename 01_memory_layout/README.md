# Module 01: Memory Layout & Cache Locality

## 🎯 Core Problem
Why does the order of variables in a `struct` change the speed of a program?

## 🧠 Technical Depth
### 1. Memory Alignment
CPUs read memory in "words" (8 bytes on 64-bit). If a 4-byte `int` is not aligned to a 4-byte boundary, the CPU must perform extra shifts and masks (or multiple fetches). Compilers insert **Padding** to avoid this.

### 2. Spatial Locality (Cache Lines)
Modern CPUs fetch data in **64-byte Cache Lines**. 
- A 24-byte struct allows only 2.6 items per cache line.
- A 16-byte struct allows 4 items per cache line.
This 50% density increase results in fewer DRAM fetches and better prefetcher performance.

## 📊 Tracked Metrics
- **Time:** Wall-clock time (ns) for 10M iterations.
- **QoR (Memory):** Byte-level footprint of the array.
- **Efficiency:** Processing time per byte.

## 🧪 Experiment
1.  Compare `BadStruct` (unfiltered order) vs. `GoodStruct` (descending size order).
2.  Inspect padding using `offsetof`.
3.  Benchmark linear iteration.

## 🎛 Experimental Controls
- **Compiler Optimizations:** `-O3` used to test production behavior.
- **Cache Size:** 10M elements (160MB-240MB) ensures we exceed L3 cache, stressing the DRAM interface.
