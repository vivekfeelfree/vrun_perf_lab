#pragma once
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <vector>

namespace lab {

    class Arena {
        struct Block {
            uint8_t* data;
            size_t size;
            size_t used;
        };

        std::vector<Block> blocks;
        size_t default_block_size;

        // Align a pointer to a power-of-two boundary
        uintptr_t align_to(uintptr_t addr, size_t alignment) {
            return (addr + alignment - 1) & ~(alignment - 1);
        }

    public:
        Arena(size_t block_size = 1024 * 1024) : default_block_size(block_size) {
            allocate_block(default_block_size);
        }

        ~Arena() {
            for (auto& block : blocks) {
                std::free(block.data);
            }
        }

        void* alloc(size_t size, size_t alignment = 8) {
            Block* current = &blocks.back();
            
            uintptr_t current_addr = reinterpret_cast<uintptr_t>(current->data + current->used);
            uintptr_t aligned_addr = align_to(current_addr, alignment);
            size_t needed_with_alignment = (aligned_addr - current_addr) + size;

            if (current->used + needed_with_alignment > current->size) {
                // Not enough space, allocate new block
                size_t new_size = std::max(default_block_size, size + alignment);
                allocate_block(new_size);
                current = &blocks.back();
                aligned_addr = align_to(reinterpret_cast<uintptr_t>(current->data), alignment);
                needed_with_alignment = (aligned_addr - reinterpret_cast<uintptr_t>(current->data)) + size;
            }

            current->used += needed_with_alignment;
            return reinterpret_cast<void*>(aligned_addr);
        }

        // Reset the arena without deallocating blocks (re-use memory!)
        void reset() {
            for (auto& block : blocks) {
                block.used = 0;
            }
        }

    private:
        void allocate_block(size_t size) {
            uint8_t* data = static_cast<uint8_t*>(std::malloc(size));
            blocks.push_back({data, size, 0});
        }
    };

} // namespace lab
