# Module 44: Clock Domain Crossing (CDC) Verification

## 🎯 Goal
Identify potential metastability risks in signals crossing asynchronous clock domains without proper synchronization.

## 🧠 Key Concept
When a signal from one clock domain is sampled by a register in another asynchronous domain, it can violate setup/hold times, leading to **metastability**. Synchronizers (like a 2-FF chain) are required to safely resolve these signals.

## 📊 Metrics to Watch
- **Violation Count:** Number of unsynchronized crossings.
- **Verification Coverage:** Percentage of paths analyzed.
