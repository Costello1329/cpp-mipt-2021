#include <algorithm>
#include <iostream>
#include <vector>
#include <new>


class small_object {}; /// 1B


int main () {
    std::vector<small_object*> ptrs;
    size_t lowest_addr = -1; /// Highest possible value (2^64 - 1).
    size_t highest_addr = 0;

    const size_t amount = 1000000;

    for (size_t i = 0; i < amount; i ++) {
        small_object* ptr = new small_object;
        /// DO SMTH HERE.
        ptrs.push_back(ptr);
        lowest_addr = std::min(lowest_addr, reinterpret_cast<size_t>(ptr));
        highest_addr = std::max(highest_addr, reinterpret_cast<size_t>(ptr));
        delete ptr;
    }

    const double fragmentation =
        static_cast<double>(highest_addr - lowest_addr) /
        static_cast<double>(sizeof(small_object)) /
        static_cast<double>(amount);

    std::cout << "Fragmentation: " << fragmentation << std::endl;
}

