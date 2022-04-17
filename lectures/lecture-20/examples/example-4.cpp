#include <iostream>



template <typename T>
struct my_allocator {
    typedef T value_type;

    T* allocate (const size_t n) const {
        std::cout << "allocate called, n = " << n << ", sizeof(T) = " << sizeof(T) << std::endl;
        return reinterpret_cast<T*>(new char[n * sizeof(T)]);
    }

    void deallocate (T* ptr, const size_t n) const {
        std::cout << "deallocate called, n = " << n << std::endl;
        delete[] reinterpret_cast<char*>(ptr);
    }
};

struct triplet {
    int a, b, c; /// 12B

    triplet (const int a, const int b, const int c): a(a), b(b), c(c) {
        std::cout <<
            "called the constructor at " << this << " with args: " <<
            a << ", " << b << ", " << c << std::endl;
    }

    ~triplet () {
        std::cout << "called the destructor of (" <<
            a << ", " << b << ", " << c << ") at " << this << std::endl;
    }
};


int main () {
    typedef std::allocator_traits<my_allocator<triplet>> alloc_traits;

    /// Creating an instance of the allocator:
    alloc_traits::allocator_type alloc; /// Type of this variable is `my_allocator<int>`

    /// Allocation:
    alloc_traits::size_type n = 5;
    alloc_traits::pointer chunk_of_data = alloc_traits::allocate(alloc, n); /// triplet*

    /// Construction:
    for (alloc_traits::size_type i = 0; i < n; i ++) {
        int a, b, c;
        /// Cin triplet
        std::cin >> a >> b >> c;

        /// Call constructor of the i-th triplet and provide
        alloc_traits::construct(alloc, chunk_of_data + i, a, b, c);
    }

    /// Destruction:
    for (alloc_traits::size_type i = 0; i < n; i ++)
        alloc_traits::destroy(alloc, chunk_of_data + i);

    /// Deallocation:
    alloc_traits::deallocate(alloc, chunk_of_data, n);
}
