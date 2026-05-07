# vrun_perf_lab: 100-Module Systems Engineering & EDA Curriculum

A production-grade curriculum designed to build deep muscle memory for systems programming, C++ intrinsics, and Electronic Design Automation (EDA) algorithms.

## 🧬 Lab Philosophy
Every module follows the **Research -> Implement -> Measure** lifecycle. We prioritize "Mechanical Sympathy"—aligning software design with hardware realities (caches, branch predictors, SIMD, and memory controllers).

## 📊 Standardized Metrics
- **Temporal:** Wall-clock time (nanoseconds), CPU cycles (ARM64 `cntvct_el0`).
- **Architectural:** Cache misses, branch mispredictions, instruction count.
- **QoR (Quality of Result):** Memory footprint (bytes), checksums, area/delay metrics.

## 📂 Laboratory Modules

### I. Foundational Systems DSA (01-10)
- **[01_Memory_Layout](./01_memory_layout/)**: Struct padding, alignment, and cache-line packing.
- **[02_Arena_Allocation](./02_arena_allocation/)**: $O(1)$ pointer-bump memory management vs. `malloc`.
- **[03_Intrusive_Lists](./03_intrusive_lists/)**: Kernel-style data structures and "multi-homing" objects.
- **[04_Bit_Vectors](./04_bit_vectors/)**: SWAR (SIMD Within A Register) for bit-parallel set operations.
- **[05_Circular_Buffers](./05_circular_buffers/)**: Power-of-two masking vs. modulo operator performance.
- **[06_Heaps](./06_heaps/)**: Cache-friendly D-ary (4-ary) heaps vs. Binary heaps.
- **[07_Hash_Maps](./07_hash_maps/)**: Robin Hood hashing (Open Addressing) for cache locality.
- **[08_Radix_Trees](./08_radix_trees/)**: Prefix matching and bit-level trie navigation.
- **[09_B_Trees](./09_b_trees/)**: Memory-resident multi-way search trees for minimized cache misses.
- **[10_Sparse_Sets](./10_sparse_sets/)**: (NEW) EnTT-style sparse sets for O(1) iteration and lookup.

### II. C++ Nuances & Architecture (11-20)
- **[11_Value_vs_Pointer](./11_value_vs_pointer/)**: Data-Oriented Design (DOD) and the indirection tax.
- **[12_Static_vs_Dynamic](./12_static_vs_dynamic/)**: Inlining impact of Templates vs. `virtual` functions.
- **[13_Custom_Iterators](./13_custom_iterators/)**: Zero-cost abstractions for intrusive data structures.
- **[14_SBO_Optimization](./14_sbo_optimization/)**: Small Buffer Optimization to avoid heap fragmentation.
- **[15_Move_Semantics](./15_move_semantics/)**: Resource stealing and Return Value Optimization (RVO).
- **[16_Type_Erasure](./16_type_erasure/)**: Performance of `std::function` vs. custom dispatcher wrappers.
- **[17_SIMD_Strings](./17_simd_strings/)**: ARM NEON intrinsics for 16-byte parallel processing.
- **[18_Lock_Free_Stack](./18_lock_free_stack/)**: Atomic CAS-based concurrency vs. Mutex serialization.
- **[19_Graph_CSR](./19_graph_csr/)**: Compressed Sparse Row layout for high-locality graph traversals.
- **[20_Cache_Oblivious](./20_cache_oblivious/)**: Recursive matrix transpose for hardware-agnostic tiling.

### III. DSA & Graph Algorithms (21-30)
- **[21_Graph_Partitioning_KL](./21_graph_partitioning_kl/)**: Kernighan-Lin heuristic for min-cut partitioning.
- **(Pending 22-30)**: Advanced flow, matching, and coloring algorithms.

### IV. Logic Synthesis (31-50)
- **[31_Logic_Synthesis_BDD](./31_logic_synthesis_bdd/)**: Binary Decision Diagrams and Structural Hashing.
- **[32_Logic_Synthesis_AIG](./32_logic_synthesis_aig/)**: And-Inverter Graphs & 2-Level Strashing.
- **[33_SAT_Solver](./33_sat_solver/)**: Boolean Satisfiability and Unit Propagation (BCP) metrics.
- **[34_Logic_Synthesis_Mapping](./34_logic_synthesis_mapping/)**: Technology Mapping using Dynamic Programming.
- **(Pending 35-50)**: Don't-care optimization, resubstitution, and FPGA mapping.

### V. Physical Design (51-80)
- **(Pending 51-80)**: Floorplanning, Placement, Routing, and Timing Analysis.

### VI. NP-Hard Algorithms (81-100)
- **(Pending 81-100)**: Travelling Salesman variants, Hypergraph Partitioning, and Advanced Heuristics.

---
*Created and maintained with a focus on empirical performance and hardware-software co-design.*
