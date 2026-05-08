# Module 73: Static Timing Analysis (STA) Sign-off

## 🎯 Goal
Verify setup and hold timing constraints for a critical path between two registers.

## 🧠 Key Concept
STA is the definitive method for validating digital circuit performance without full-scale simulation. It calculates the **Setup Slack** (ensuring data arrives before the next clock edge) and **Hold Slack** (ensuring data stays stable long enough to be sampled), accounting for logic delays, wire delays, and clock skew.

## 📊 Metrics to Watch
- **Worst Negative Slack (WNS):** The most severe timing violation in the design.
- **Total Negative Slack (TNS):** The sum of all negative slacks across all paths.
