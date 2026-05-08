# Module 48: Power Analysis

## 🎯 Goal
Estimate dynamic power consumption by tracking the switching activity of logic nodes during simulation.

## 🧠 Key Concept
Dynamic power in CMOS circuits is primarily dissipated during logic transitions (0 $\rightarrow$ 1 or 1 $\rightarrow$ 0) due to the charging and discharging of parasitic capacitances. This module calculates switching activity as the average number of transitions per node per cycle.

## 📊 Metrics to Watch
- **Total Switches:** Cumulative count of node transitions.
- **Switching Activity:** Average transition rate across all gates.
