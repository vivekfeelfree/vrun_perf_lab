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
- **[10_Sparse_Sets](./10_sparse_sets/)**: EnTT-style sparse sets for O(1) iteration and lookup.

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
- **[22_Max_Flow_Dinic](./22_max_flow_dinic/)**: Dinic's algorithm for maximum network flow.
- **[23_Min_Cost_Max_Flow](./23_min_cost_max_flow/)**: Successive Shortest Path algorithm for MCMF.
- **[24_Bipartite_Matching](./24_bipartite_matching/)**: Hopcroft-Karp $O(E \sqrt{V})$ matching.
- **[25_SCC_Tarjan](./25_scc_tarjan/)**: Tarjan's algorithm for strongly connected components.
- **[26_Topo_Sort_Critical_Path](./26_topo_sort_critical_path/)**: DAG analysis for Static Timing Analysis.
- **[27_DSU_Disjoint_Set](./27_dsu_disjoint_set/)**: Near-constant time set union and find.
- **[28_Segment_Trees](./28_segment_trees/)**: Logarithmic range queries and point updates.
- **[29_AStar_Search](./29_astar_search/)**: Heuristic-guided shortest path on grids.
- **[30_MST_Kruskal](./30_mst_kruskal/)**: Minimum Spanning Tree using DSU.

### IV. Logic Synthesis (31-50)
- **[31_Logic_Synthesis_BDD](./31_logic_synthesis_bdd/)**: Binary Decision Diagrams and Structural Hashing.
- **[32_Logic_Synthesis_AIG](./32_logic_synthesis_aig/)**: And-Inverter Graphs & 2-Level Strashing.
- **[33_SAT_Solver](./33_sat_solver/)**: Boolean Satisfiability and Unit Propagation (BCP).
- **[34_Logic_Synthesis_Mapping](./34_logic_synthesis_mapping/)**: Technology Mapping using Dynamic Programming.
- **[35_FPGA_LUT_Mapping](./35_fpga_lut_mapping/)**: K-input LUT covering heuristics.
- **[36_Boolean_Rewriting](./36_boolean_rewriting/)**: Local AIG sub-graph optimization.
- **[37_Equivalence_Checking](./37_equivalence_checking/)**: Miter-based formal verification and simulation.
- **[38_Dont_Care_Optimization](./38_dont_care_optimization/)**: ODC identification for logic pruning.
- **[39_Logic_Refactoring](./39_logic_refactoring/)**: Algebraic factoring for literal reduction.
- **[40_State_Machine_Minimization](./40_state_machine_minimization/)**: Moore's algorithm for FSM reduction.
- **[41_BDD_Sifting](./41_bdd_sifting/)**: Dynamic variable reordering for BDD size.
- **[42_AIG_Balancing](./42_aig_balancing/)**: Associative restructuring for logic depth reduction.
- **[43_Gate_Sizing](./43_gate_sizing/)**: Timing-driven area optimization via cell sizing.
- **[44_Clock_Domain_Crossing](./44_clock_domain_crossing/)**: CDC verification and metastability analysis.
- **[45_Formal_Induction](./45_formal_induction/)**: k-Induction for property invariant proving.
- **[46_Logic_Sim_Event](./46_logic_sim_event/)**: Event-driven logic simulation efficiency.
- **[47_Logic_Sim_Cycle](./47_logic_sim_cycle/)**: Bit-parallel cycle-based simulation (SWAR).
- **[48_Power_Analysis](./48_power_analysis/)**: Switching activity-based dynamic power estimation.
- **[49_Synthesis_Report](./49_synthesis_report/)**: Metric aggregation and QoR summarization.
- **[50_Resource_Estimation](./50_resource_estimation/)**: Early-stage hardware utilization prediction.

### V. Physical Design (51-80)
- **[51_Floorplanning_SA](./51_floorplanning_sa/)**: Simulated Annealing for macro block placement.
- **[52_HPWL_Estimation](./52_hpwl_estimation/)**: Half-Perimeter Wirelength estimation for placement.
- **[53_Partitioning_Placement](./53_partitioning_placement/)**: Recursive min-cut for global placement.
- **[54_Analytical_Placement](./54_analytical_placement/)**: Force-directed analytical placement.
- **[55_Maze_Routing](./55_maze_routing/)**: Lee's algorithm for global maze routing.
- **[56_Steiner_Tree](./56_steiner_tree/)**: MST-based approximation for RSMT.
- **[57_Channel_Routing](./57_channel_routing/)**: Left-Edge algorithm for track assignment.
- **[58_Clock_Tree_Synthesis](./58_clock_tree_synthesis/)**: H-Tree construction for clock distribution.
- **[59_Power_Grid_Analysis](./59_power_grid_analysis/)**: IR drop calculation using iterative solvers.
- **[60_Parasitic_Extraction](./60_parasitic_extraction/)**: Elmore delay estimation for RC networks.
- **[61_Detailed_Routing](./61_detailed_routing/)**: Multi-layer A* search with via costs.
- **[62_Design_Rule_Checking](./62_design_rule_checking/)**: Geometric spacing check heuristics.
- **[63_Signal_Integrity](./63_signal_integrity/)**: Crosstalk estimation for parallel wires.
- **[64_Antenna_Checking](./64_antenna_checking/)**: Metal-to-gate area ratio analysis.
- **[65_Metal_Fill](./65_metal_fill/)**: Density optimization for CMP uniformity.
- **[66_Std_Cell_Rows](./66_std_cell_rows/)**: Placement constraint generation.
- **[67_ECO_Logic_Patch](./67_eco_logic_patch/)**: Late-stage logic modification using spare cells.
- **[68_Buffer_Insertion](./68_buffer_insertion/)**: Timing closure via RC chain fragmentation.
- **[69_Yield_Analysis](./69_yield_analysis/)**: Monte Carlo simulation for process variation.
- **[70_GDSII_Streamer](./70_gdsii_streamer/)**: Binary serialization for mask data.
- **[71_LVS_Check](./71_lvs_check/)**: Connectivity verification via graph signatures.
- **[72_Parasitic_Reduction](./72_parasitic_reduction/)**: Pi-model simplification for RC networks.
- **[73_STA_Signoff](./73_sta_signoff/)**: Setup and hold slack validation.
- **[74_Electromigration](./74_electromigration/)**: Reliability analysis via Black's Law.
- **[75_Thermal_Analysis](./75_thermal_analysis/)**: 2D heat diffusion modeling.
- **[76_Logical_Effort](./76_logical_effort/)**: Path optimization and stage scaling.
- **[77_Glitch_Analysis](./77_glitch_analysis/)**: Static hazard detection in logic.
- **[78_SER_Soft_Error](./78_ser_soft_error/)**: Particle strike susceptibility estimation.
- **[79_DFT_Scan_Insertion](./79_dft_scan_insertion/)**: Testability transformation and overhead.
- **[80_Tapeout_Signoff](./80_tapeout_signoff_checklist/)**: Final design check aggregation.

### VI. NP-Hard Algorithms (81-100)
- **[81_TSP_Simulated_Annealing](./81_tsp_simulated_annealing/)**: Probabilistic metaheuristic for Traveling Salesman.
- **[82_Hypergraph_Partitioning_FM](./82_hypergraph_partitioning_fm/)**: Fiduccia-Mattheyses iterative min-cut.
- **[83_SAT_WalkSAT](./83_sat_walksat/)**: Stochastic local search for Boolean satisfiability.
- **[84_Knapsack_DP](./84_knapsack_dp/)**: Optimal resource allocation via dynamic programming.
- **[85_Max_Clique_BB](./85_max_clique_bb/)**: Branch & Bound search for fully connected subgraphs.
- **[86_Graph_Coloring_DSATUR](./86_graph_coloring_dsatur/)**: Saturated degree heuristic for register allocation.
- **[87_LCS_DP](./87_lcs_dp/)**: Longest Common Subsequence for revision comparison.
- **[88_Huffman_Coding](./88_huffman_coding/)**: Optimal prefix-free coding for data compression.
- **[89_Vertex_Cover_Approx](./89_vertex_cover_approx/)**: Greedy 2-approximation for minimum vertex cover.
- **[90_Hamiltonian_Path_Backtrack](./90_hamiltonian_path_backtrack/)**: Exhaustive search for single-visit paths.
- **[91_Longest_Path_DAG](./91_longest_path_dag/)**: Linear-time critical path analysis in DAGs.
- **[92_Subset_Sum_DP](./92_subset_sum_dp/)**: Pseudo-polynomial search for target subsets.
- **[93_Job_Scheduling_EDF](./93_job_scheduling_edf/)**: Optimal real-time task scheduling.
- **[94_Sudoku_Backtrack](./94_sudoku_backtrack/)**: Recursive constraint satisfaction search.
- **[95_Matrix_Chain_DP](./95_matrix_chain_dp/)**: Optimal parenthesization for multiplication efficiency.
- **[96_KMeans_Clustering](./96_kmeans_clustering/)**: Iterative centroid-based data partitioning.
- **[97_Prime_Factorization](./97_prime_factorization/)**: Trial division for composite number decomposition.
- **[98_Rabin_Karp_String_Match](./98_rabin_karp_string_match/)**: Rolling hash-based efficient pattern search.
- **[99_Simulated_Annealing_Generic](./99_simulated_annealing_generic/)**: Abstract framework for combinatorial optimization.
- **[100_MCTS_Algorithm](./100_mcts_algorithm/)**: Monte Carlo Tree Search for complex decision trees.

---
*Created and maintained with a focus on empirical performance and hardware-software co-design.*
