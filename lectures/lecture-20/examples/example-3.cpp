#include <iostream>


template <typename T>
struct simple_allocator {
    typedef T value_type; /// I'm creating a new type called value_type which is the same type as T.
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    /// Other typedefs were deprecated in C++17 and removed in C++20.

    T* allocate (const size_t n) {
        std::cout << "Allocating " << n << " objects" << std::endl;
        return reinterpret_cast<T*>(new char[n * sizeof(T)]);
    }

    void deallocate (T* ptr, const size_t n) {
        std::cout << "Deallocating " << n << " objects" << std::endl;
        delete[] reinterpret_cast<char*>(ptr);
    }

    /// Deprecated in C++17 and removed in C++20.
    template <typename U, typename ...Args>
    void construct (U* ptr, const Args... args) { new (ptr) T(args...); }

    /// Deprecated in C++17 and removed in C++20.
    template <typename U>
    void destroy (U* ptr) { ptr->~T(); }
};

struct logger {
    explicit logger (const size_t id): _id(id) { std::cout << "Constructed at " << this << std::endl; }
    ~logger () { std::cout << "Destructed at " << this << std::endl; }
    void print (const std::string &str) const { std::cout << _id << ": " << str << std::endl; }

private:
    size_t _id;
};

template <typename Alloc>
void do_some_operations_with_allocator (Alloc& alloc) {
    const size_t n = 2;

    typename Alloc::value_type* chunk = alloc.allocate(n);

    for (size_t i = 0; i < n; i ++)
        alloc.construct(chunk + i, i + 1);

    chunk[0].print("hello");
    chunk[1].print("bye");

    for (size_t i = 0; i < n; i ++)
        alloc.destroy(chunk + i);

    alloc.deallocate(chunk, n);
}

int main () {
    simple_allocator<logger> alloc;
    do_some_operations_with_allocator(alloc);
}
