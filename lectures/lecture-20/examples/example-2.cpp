#include <iostream>
#include <memory>


struct logger {
    explicit logger (const int) { std::cout << "Constructed at " << this << std::endl; }
    ~logger () { std::cout << "Destructed at " << this << std::endl; }
};

template <typename Alloc>
void do_some_operations_with_allocator (Alloc& alloc) {
    const size_t n = 2;

    typename Alloc::value_type* chunk = alloc.allocate(n);

    for (size_t i = 0; i < n; i ++)
        alloc.construct(chunk + i, i + 1);

    for (size_t i = 0; i < n; i ++)
        alloc.destroy(chunk + i);

    alloc.deallocate(chunk, n);
}

int main () {
    std::allocator<logger> logger_alloc;
    do_some_operations_with_allocator(logger_alloc);

    std::allocator<int> int_alloc;
    do_some_operations_with_allocator(int_alloc);
}
