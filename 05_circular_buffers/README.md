# Module 05: Circular Buffers & Power-of-Two Masking

## The Core Problem: Producer-Consumer Communication
In a kernel or a real-time system, you often have a fast producer (e.g., a serial port) and a slower consumer. We need a fixed-size queue that:
1.  **Never Allocates:** Allocation is too slow and non-deterministic.
2.  **Overwrites or Blocks:** If the buffer is full, we must decide what to do.

## 1. The Naive Circular Buffer
We use two pointers (or indices): `head` and `tail`.
- `Push`: Put data at `tail`, then `tail = (tail + 1) % size`.
- `Pop`: Get data from `head`, then `head = (head + 1) % size`.

**The Performance Killer:** The `%` (modulo) operator. On many CPUs, an integer division/modulo can take 20-40 cycles.

## 2. The Power-of-Two Optimization
If `size` is a power of two (e.g., 256, 1024, 65536), we can use a mathematical trick:
`(x % size)` is identical to `(x & (size - 1))`.

**The Performance Win:** The `&` (AND) instruction takes only 1 cycle. This is a massive speedup for high-frequency buffers.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **Modulo-based Buffer:** A buffer with an arbitrary size (e.g., 1000).
2.  **Mask-based Buffer:** A buffer with a power-of-two size (e.g., 1024).

## 🎛 Experimental Controls
- **Buffer Size:** Does the gap between `%` and `&` stay the same as the buffer grows?
- **Throughput:** Measure how many million items per second we can push/pop in each version.
