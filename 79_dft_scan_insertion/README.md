# Module 79: DFT Scan Chain Insertion

## 🎯 Goal
Transform standard flip-flops into scan-flops and measure the impact on area and testability.

## 🧠 Key Concept
Design for Test (DFT) makes internal chip states observable and controllable from external pins. Scan chain insertion replaces standard registers with scan-flops, allowing the chip to be shifted into a "test mode" where data can be shifted in and out. This is essential for post-manufacturing testing.

## 📊 Metrics to Watch
- **Area Overhead:** Incremental area increase due to scan-flops and routing.
- **Fault Coverage:** Percentage of circuit faults detectable through the scan chain.
