# vrun_perf_lab: Systems Engineering & DSA Laboratory

Broader collection of simple to complex workloads and hand made benchmarks to help learning production grade DSA stack with the help of C++ nuances and intrinsics from the scratch.

## 🧬 Lab Philosophy
Every module in this lab follows the **Research -> Implement -> Measure** lifecycle. We prioritize "Mechanical Sympathy"—aligning software design with hardware realities (caches, branch predictors, SIMD, and memory controllers).

## 📊 Standardized Metrics
- **Temporal:** Wall-clock time (nanoseconds), CPU cycles (ARM64 `cntvct_el0`).
- **Architectural:** Cache misses, branch mispredictions, instruction count.
- **QoR (Quality of Result):** Memory footprint (bytes), node counts, logic depth, decision density.

## 📂 Laboratory Modules

### I. Foundational Systems DSA (01-09)
- **[01_Memory_Layout](./01_memory_layout/)**: Struct padding, alignment, and cache-line packing.
- **[02_Arena_Allocation](./02_arena_allocation/)**: $O(1)$ pointer-bump memory management vs. `malloc`.
- **[03_Intrusive_Lists](./03_intrusive_lists/)**: Kernel-style data structures and "multi-homing" objects.
- **[04_Bit_Vectors](./04_bit_vectors/)**: SWAR (SIMD Within A Register) for bit-parallel set operations.
- **[05_Circular_Buffers](./05_circular_buffers/)**: Power-of-two masking vs. modulo operator performance.
- **[06_Heaps](./06_heaps/)**: Cache-friendly D-ary (4-ary) heaps vs. Binary heaps.
- **[07_Hash_Maps](./07_hash_maps/)**: Robin Hood hashing (Open Addressing) for cache locality.
- **[08_Radix_Trees](./08_radix_trees/)**: Prefix matching and bit-level trie navigation.
- **[09_B_Trees](./09_b_trees/)**: Memory-resident multi-way search trees for minimized cache misses.

### II. C++ Nuances & Architecture (10-19)
- **[10_Value_vs_Pointer](./10_value_vs_pointer/)**: Data-Oriented Design (DOD) and the indirection tax.
- **[11_Static_vs_Dynamic](./11_static_vs_dynamic/)**: Inlining impact of Templates vs. `virtual` functions.
- **[12_Custom_Iterators](./12_custom_iterators/)**: Zero-cost abstractions for intrusive data structures.
- **[13_SBO_Optimization](./13_sbo_optimization/)**: Small Buffer Optimization to avoid heap fragmentation.
- **[14_Move_Semantics](./14_move_semantics/)**: Resource stealing and Return Value Optimization (RVO).
- **[15_Type_Erasure](./15_type_erasure/)**: Performance of `std::function` vs. custom dispatcher wrappers.
- **[16_SIMD_Strings](./16_simd_strings/)**: ARM NEON intrinsics for 16-byte parallel processing.
- **[17_Lock_Free_Stack](./17_lock_free_stack/)**: Atomic CAS-based concurrency vs. Mutex serialization.
- **[18_Graph_CSR](./18_graph_csr/)**: Compressed Sparse Row layout for high-locality graph traversals.
- **[19_Cache_Oblivious](./19_cache_oblivious/)**: Recursive matrix transpose for hardware-agnostic tiling.

### III. EDA Tier: Logic Synthesis (20-29)
- **[20_Logic_Synthesis_BDD](./20_logic_synthesis_bdd/)**: Binary Decision Diagrams and Structural Hashing.
- **[21_Logic_Synthesis_AIG](./21_logic_synthesis_aig/)**: And-Inverter Graphs & 2-Level Strashing.
- **[22_SAT_Solver](./22_sat_solver/)**: Boolean Satisfiability and Unit Propagation (BCP) metrics.

---
*Created and maintained with a focus on empirical performance and hardware-software co-design.*
