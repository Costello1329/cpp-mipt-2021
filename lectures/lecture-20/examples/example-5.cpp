#include <iostream>


template <typename T>
class linear_allocator {
public:
    typedef T value_type;

    explicit linear_allocator (const size_t buffer_size = k_buffer_size):
        _buffer_size(buffer_size),
        _buffer(reinterpret_cast<T*>(new (std::nothrow) char[sizeof(T) * k_buffer_size])),
        _allocations_count(0)
    {}

    ~linear_allocator () { delete[] reinterpret_cast<char*>(_buffer); };

    T* allocate (const size_t n) {
        std::cout << "Allocating memory for storing n = " << n << " objects" << std::endl;

        /// We dont have enough space for allocating n objects:
        if (_allocations_count + n > _buffer_size)
            throw std::bad_alloc(); /// No space left, so we need to throw an exception.

        const size_t current_allocations_count = _allocations_count;
        _allocations_count += n;
        return _buffer + current_allocations_count;
    }

    void deallocate (T*, const size_t n) const noexcept {
        std::cout << "Deallocating memory with n = " << n << " objects" << std::endl;
    }

    size_t max_size () const noexcept { return _buffer_size; }

private:
    const static size_t k_buffer_size = 1024;

    size_t _buffer_size;
    T* _buffer;
    size_t _allocations_count;
};

struct logger {
    explicit logger (const size_t id): _id(id) { std::cout << "Constructed at " << this << std::endl; }
    ~logger () { std::cout << "Destructed at " << this << std::endl; }
    void print (const std::string &str) const { std::cout << _id << ": " << str << std::endl; }

private:
    size_t _id;
};

int main () {
    typedef std::allocator_traits<linear_allocator<logger>> alloc_traits;

    alloc_traits::allocator_type alloc;

    std::cout << "Max size supported by an allocator: " << alloc_traits::max_size(alloc) << std::endl;

    alloc_traits::size_type n = 1025;

    alloc_traits::pointer chunk = alloc_traits::allocate(alloc, n);

    for (size_t i = 0; i < n; i ++)
        alloc_traits::construct(alloc, chunk + i, i + 1);

    chunk[0].print("hello");
    chunk[1].print("bye");

    for (size_t i = 0; i < n; i ++)
        alloc_traits::destroy(alloc, chunk + i);

    alloc_traits::deallocate(alloc, chunk, n);
}
