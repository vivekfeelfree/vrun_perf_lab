# Module 16: SIMD-Accelerated String Search (ARM NEON)

## The Core Problem: The Byte-at-a-Time Bottleneck
A standard `std::string::find` or a manual `for` loop looks like this:
```cpp
for (char c : str) {
    if (c == target) return found;
}
```
**The Problem:** The CPU is capable of 64-bit or 128-bit operations, but we are using it to process 8-bit characters. This leaves ~94% of the execution units idle.

## 1. SIMD: Single Instruction, Multiple Data
On your `aarch64` machine, the **NEON** unit provides 128-bit registers (`v0`-`v31`). 
One 128-bit register can hold **16 characters** (uint8_t).

### The NEON Strategy:
1.  **Broadcast:** Fill a 128-bit register with 16 copies of the `target` character.
2.  **Load:** Load 16 bytes from the string into another 128-bit register.
3.  **Compare:** Use the `vceqq_u8` (Vector Compare Equal) instruction. This compares all 16 positions in parallel and returns a "mask" where matches are `0xFF` and non-matches are `0x00`.
4.  **Check:** Check if any byte in the mask is non-zero.

## 2. Mechanical Sympathy: Data Alignment
SIMD is fastest when memory is aligned to the vector size (16 bytes). If the string starts at an unaligned address, the CPU might have to perform two memory fetches to fill one register.

## 3. The Experiment
In `main.cpp`, we will implement:
1.  **Naive Search:** A simple `char` loop.
2.  **NEON Search:** Using ARM64 intrinsics (`<arm_neon.h>`).

## 🎛 Experimental Controls
- **String Length:** Compare small strings vs. 100MB files.
- **Match Frequency:** Does the speed change if there are many matches vs. no matches?
