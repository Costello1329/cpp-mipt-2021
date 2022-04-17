#include <iostream>
#include <new>


class point {
public:
    point (int x, int y, int z): _x(x), _y(y), _z(z) { std::cout << "Constructed" << std::endl; }
    ~point () { std::cout << "Destructed" << std::endl; }

    int _x, _y, _z; /// 12 bytes
};


void* operator new (size_t bytes_count) {
    std::cout << "allocating " << bytes_count << " bytes" << std::endl;
    return malloc(bytes_count);
}

void operator delete (void* ptr) noexcept {
    std::cout << "deallocating chunk at " << ptr << std::endl;
    free(ptr);
}


void* operator new (size_t bytes_count, const std::nothrow_t&) noexcept {
    std::cout << "allocating (nothrow) " << bytes_count << " bytes" << std::endl;
    return malloc(bytes_count);
}

void operator delete (void* ptr, const std::nothrow_t&) noexcept {
    std::cout << "deallocating (nothrow) chunk at " << ptr << std::endl;
    free(ptr);
}


int main () {
    std::cout << "Standard versions:" << std::endl;
    point* first = new point(1, 2, 3);
    delete first;

    std::cout << std::endl << "Nothrow versions:" << std::endl;
    point* second = new (std::nothrow) point(3, 2, 1);
    second->~point();
    operator delete(second, std::nothrow);
}
