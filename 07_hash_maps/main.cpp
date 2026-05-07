/**
 * EXPERIMENT: Robin Hood Hashing (Open Addressing)
 * 
 * GOAL: Compare the cache-friendly "Flat Map" approach against 
 * the standard library's "Chaining" approach.
 */

#include "../include/harness.hpp"
#include <vector>
#include <unordered_map>
#include <optional>

/**
 * A simplified Robin Hood Hash Map.
 * Note: To keep the lab focused, we use a fixed size and simple integer keys.
 */
template <typename K, typename V>
class RobinHoodMap {
    struct Entry {
        K key;
        V value;
        int psl; // Probe Sequence Length (Distance from preferred bucket)
        bool occupied = false;
    };

    std::vector<Entry> table;
    size_t table_size;

    size_t hash(K key) const {
        // Simple hash for experimentation
        return static_cast<size_t>(key) % table_size;
    }

public:
    RobinHoodMap(size_t size) : table_size(size) {
        table.resize(table_size);
    }

    void insert(K key, V value) {
        size_t pos = hash(key);
        Entry new_entry{key, value, 0, true};

        while (true) {
            if (!table[pos].occupied) {
                table[pos] = new_entry;
                return;
            }

            // Robin Hood Logic: If current entry is "richer" than our 
            // new entry (has smaller PSL), we swap them.
            if (new_entry.psl > table[pos].psl) {
                std::swap(new_entry, table[pos]);
            }

            // Move to next bucket
            pos = (pos + 1) % table_size;
            new_entry.psl++;
            
            // In a production map, we would resize here if we loop too much
        }
    }

    std::optional<V> get(K key) const {
        size_t pos = hash(key);
        int current_psl = 0;

        while (table[pos].occupied) {
            if (table[pos].key == key) return table[pos].value;

            // Optimization: If the current entry's PSL is smaller than
            // our search PSL, the key CANNOT be in the map (it would have 
            // been swapped by Robin Hood logic).
            if (current_psl > table[pos].psl) return std::nullopt;

            pos = (pos + 1) % table_size;
            current_psl++;
            if (current_psl >= (int)table_size) break;
        }
        return std::nullopt;
    }
};

const int ITEM_COUNT = 500'000;
const int TABLE_SIZE = 1'000'000; // 50% load factor

int main() {
    std::cout << "--- Robin Hood Hash Map Laboratory ---" << std::endl;

    std::vector<int> keys(ITEM_COUNT);
    for(int i=0; i<ITEM_COUNT; ++i) keys[i] = rand();

    // Benchmark 1: std::unordered_map (Chaining)
    {
        std::unordered_map<int, int> std_map;
        lab::Benchmark b("std::unordered_map (Insert)");
        for(int k : keys) std_map[k] = k;
    }

    // Benchmark 2: RobinHoodMap (Open Addressing)
    {
        RobinHoodMap<int, int> rh_map(TABLE_SIZE);
        lab::Benchmark b("RobinHoodMap (Insert)");
        for(int k : keys) rh_map.insert(k, k);
    }

    // Benchmark 3: Lookups
    {
        std::unordered_map<int, int> std_map;
        for(int k : keys) std_map[k] = k;
        
        lab::Benchmark b("std::unordered_map (Lookup)");
        long long sum = 0;
        for(int k : keys) sum += std_map[k];
        lab::escape(&sum);
    }

    {
        RobinHoodMap<int, int> rh_map(TABLE_SIZE);
        for(int k : keys) rh_map.insert(k, k);

        lab::Benchmark b("RobinHoodMap (Lookup)");
        long long sum = 0;
        for(int k : keys) {
            auto val = rh_map.get(k);
            if(val) sum += *val;
        }
        lab::escape(&sum);
    }

    return 0;
}
