#include <algorithm>
#include <iostream>
#include <vector>
#include <new>


class chunk_manager {
private:
    const size_t k_buffer_size = 1024;
    size_t _type_size;
    size_t _allocations_count;
    size_t _deallocations_count;
    void* _buffer;

public:
    explicit chunk_manager (const size_t type_size):
        _type_size(type_size),
        _allocations_count(0),
        _deallocations_count(0),
        _buffer(malloc(_type_size * k_buffer_size))
    {}

    ~chunk_manager () { free(_buffer); }

    void* alloc () {
        if (_allocations_count == k_buffer_size)
            throw std::bad_alloc();

        return static_cast<void*>(static_cast<char*>(_buffer) + _type_size * (_allocations_count ++));
    }

    void dealloc () { ++ _deallocations_count; }
};


void* operator new (const size_t bytes_count, chunk_manager* manager) {
    return manager->alloc();
}

template <typename T>
void operator delete (void* ptr, chunk_manager* manager) noexcept {
    static_cast<T*>(ptr)->~T();
    manager->dealloc();
}


class small_object { int a, b, c; }; /// 12B

int main () {
    chunk_manager manager(sizeof(small_object));

    std::vector<small_object*> ptrs;
    size_t lowest_addr = -1;
    size_t highest_addr = 0;

    const size_t amount = 1024;

    for (size_t i = 0; i < amount; i ++) {
        small_object *ptr = new (&manager) small_object;

        /// DO SOMETHING HERE.
        ptrs.push_back(ptr);
        lowest_addr = std::min(lowest_addr, reinterpret_cast<size_t>(ptr));
        highest_addr = std::max(highest_addr, reinterpret_cast<size_t>(ptr));
        operator delete<small_object> (ptr, &manager);
    }

    const double fragmentation =
        (
            static_cast<double>(highest_addr - lowest_addr) +
            static_cast<double>(sizeof(small_object))
        ) / static_cast<double>(sizeof(small_object)) / static_cast<double>(amount);

    std::cout << "Fragmentation: " << fragmentation << std::endl;
}
