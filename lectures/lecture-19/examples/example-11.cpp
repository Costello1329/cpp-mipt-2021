#include <iostream>
#include <new>


class point {
public:
    point (int x, int y, int z): _x(x), _y(y), _z(z) { std::cout << "Constructed" << std::endl; }
    ~point () { std::cout << "Destructed" << std::endl; }

    int _x, _y, _z; /// 12 bytes
};


void* operator new (size_t bytes_count, size_t max_bytes_count) {
    if (bytes_count > max_bytes_count)
        throw std::bad_alloc();

    void* ptr = malloc(bytes_count);
    std::cout << "Allocated successfully" << std::endl;

    return ptr;
}

template <typename T>
void operator delete (void* ptr, size_t max_bytes_count) noexcept {
    free(ptr);
    std::cout << "Deallocated successfully" << std::endl;
}

int main () {
    size_t max_bytes_count;
    std::cout << "Enter max bytes count for buffer allocations: ";
    std::cin >> max_bytes_count;

    try {
        point* first = new (max_bytes_count) point(1, 2, 3);
        operator delete<point>(first, max_bytes_count);
    } catch (...) {
        std::cout << "Struct is too big" << std::endl;
    }
}
