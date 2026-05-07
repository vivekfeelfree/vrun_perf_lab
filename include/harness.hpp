#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

namespace lab {

    // Prevent compiler from optimizing away a value
    inline void escape(void* p) {
        asm volatile("" : : "g"(p) : "memory");
    }

    // Force compiler to treat memory as modified
    inline void clobber() {
        asm volatile("" : : : "memory");
    }

    class Benchmark {
        std::chrono::high_resolution_clock::time_point start_time;
        std::string name;

    public:
        Benchmark(std::string n) : name(n) {
            start_time = std::chrono::high_resolution_clock::now();
        }

        ~Benchmark() {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
            std::cout << "[BENCH] " << std::left << std::setw(30) << name 
                      << ": " << std::right << std::setw(12) << duration << " ns" << std::endl;
        }
    };

    // A simple way to measure CPU cycles on ARM64
    inline uint64_t read_cycles() {
        uint64_t val;
        // Read Virtual Count register
        asm volatile("mrs %0, cntvct_el0" : "=r" (val));
        return val;
    }

    /**
     * QoR Tracker: Memory and Integrity
     */
    inline void print_qor(const std::string& label, size_t memory_bytes, size_t integrity_check = 0) {
        std::cout << "[QoR] " << std::left << std::setw(30) << label 
                  << " | Memory: " << std::right << std::setw(10) << memory_bytes << " bytes"
                  << (integrity_check ? " | Checksum: " + std::to_string(integrity_check) : "")
                  << std::endl;
    }

} // namespace lab
