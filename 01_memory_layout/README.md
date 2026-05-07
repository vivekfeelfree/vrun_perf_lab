# Module 01: Memory Layout & Mechanical Sympathy

## The Core Question
Why does the order of variables in a `struct` change the speed of a program?

## 1. The Hardware Reality: Memory Alignment
CPUs do not read memory byte-by-byte. They read in "words" (usually 8 bytes on 64-bit systems). If a 4-byte `int` is stored at a memory address that isn't a multiple of 4, the CPU might have to:
1.  Read two different 8-byte words.
2.  Shift and mask the bits to "stitch" the integer back together.

To avoid this performance penalty, compilers insert **Padding**.

### Example: The "Bad" Layout
```cpp
struct BadStruct {
    char a;      // 1 byte
    // 7 bytes of hidden padding here!
    double b;    // 8 bytes (must start on 8-byte boundary)
    char c;      // 1 byte
    // 3 bytes of hidden padding here!
    int d;       // 4 bytes
    // 4 bytes of tail padding!
}; // Total: 24 bytes
```

### The "Good" Layout (Descending Size)
By sorting members from largest to smallest, we minimize holes:
```cpp
struct GoodStruct {
    double b;    // 8 bytes
    int d;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // 2 bytes of padding at the end
}; // Total: 16 bytes
```

## 2. The Cache Factor
Modern CPUs have **Cache Lines** (typically 64 bytes). When you access one byte, the CPU fetches the entire 64-byte line from RAM into the L1 Cache.

- **BadStruct (24 bytes):** Only ~2.6 structs fit in one cache line.
- **GoodStruct (16 bytes):** Exactly 4 structs fit in one cache line.

**Impact:** Packing data more tightly means 50% more data in your cache, leading to fewer expensive trips to main memory (RAM).

## 3. The Experiment
In `main.cpp`, we:
1.  Use `offsetof` to reveal the "invisible" padding bytes.
2.  Benchmark a tight loop iterating over 10 million elements.
3.  Observe how the 16-byte struct outperforms the 24-byte struct purely due to cache efficiency.

## 🎛 Experimental Controls
You can modify `ELEMENT_COUNT` in `main.cpp` to see how the performance gap grows as the data exceeds the size of your L2 or L3 cache.
