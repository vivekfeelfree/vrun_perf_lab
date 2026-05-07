#pragma once
#include <cstddef>

namespace lab {

    // The "Hook" that must be embedded in the user's struct
    struct ListLink {
        ListLink* next = nullptr;
        ListLink* prev = nullptr;

        bool is_linked() const { return next != nullptr; }
    };

    class IntrusiveList {
    public:
        ListLink head; // Sentinel node
        size_t count = 0;
        IntrusiveList() {
            head.next = &head;
            head.prev = &head;
        }

        void push_back(ListLink* link) {
            link->next = &head;
            link->prev = head.prev;
            head.prev->next = link;
            head.prev = link;
            count++;
        }

        void push_front(ListLink* link) {
            link->next = head.next;
            link->prev = &head;
            head.next->prev = link;
            head.next = link;
            count++;
        }

        void remove(ListLink* link) {
            if (!link->next) return;
            link->prev->next = link->next;
            link->next->prev = link->prev;
            link->next = nullptr;
            link->prev = nullptr;
            count--;
        }

        // --- NEW: Iterator Support ---
        template<typename T, ListLink T::*Member>
        class Iterator {
            ListLink* curr;
        public:
            Iterator(ListLink* p) : curr(p) {}
            T& operator*() { return *IntrusiveList::container_of<T, Member>(curr); }
            T* operator->() { return IntrusiveList::container_of<T, Member>(curr); }
            Iterator& operator++() { curr = curr->next; return *this; }
            bool operator!=(const Iterator& other) const { return curr != other.curr; }
        };

        template<typename T, ListLink T::*Member>
        Iterator<T, Member> begin_at() { return Iterator<T, Member>(head.next); }

        template<typename T, ListLink T::*Member>
        Iterator<T, Member> end_at() { return Iterator<T, Member>(&head); }
        // -----------------------------
        bool empty() const { return count == 0; }
        size_t size() const { return count; }

        // The Magic: Convert a link pointer back to the containing struct
        template<typename T, ListLink T::*Member>
        static T* container_of(ListLink* ptr) {
            // Since reinterpret_cast is not allowed in constexpr, 
            // we use a regular static function. Modern compilers 
            // will still optimize this to a constant subtraction.
            const size_t offset = (size_t)&(static_cast<T*>(nullptr)->*Member);
            return (T*)((char*)ptr - offset);
        }
    };

} // namespace lab
