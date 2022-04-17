#include <iostream>



template <typename vt>
struct simple_array {
    static_assert(std::is_default_constructible_v<vt>, "vt type must be default constructible");
    static_assert(std::is_destructible_v<vt>, "vt type must be default destructible");
    static_assert(std::is_copy_assignable_v<vt>, "vt type must be copy assignable");

    explicit simple_array (const size_t size) noexcept(std::is_nothrow_default_constructible_v<vt>):
        _size(size), _data(new (std::nothrow) vt[size]) {}

    ~simple_array () noexcept(std::is_nothrow_destructible_v<vt>) {
        for (size_t i = 0; i < _size; i ++)
            _data[i].~vt();

        operator delete[] (_data, std::nothrow);
    }

    simple_array (const simple_array& other) noexcept(
        std::is_nothrow_default_constructible_v<vt> &&
        std::is_nothrow_copy_assignable_v<vt>
    ): simple_array(other._size) {
        /// Deep copy here, takes O(_size) time.
        for (size_t i = 0; i < _size; i ++)
            _data[i] = other._data[i]; /// Calling the operator= for every object in the array
    }

    simple_array& operator= (const simple_array& other) & noexcept(
        std::is_nothrow_default_constructible_v<vt> &&
        std::is_nothrow_copy_assignable_v<vt> &&
        std::is_nothrow_destructible_v<vt>
    ) {
        if (this != &other) {
            this->~simple_array(); /// may throw if the destructor of the vt type is not nothrow
            /** may throw if the default constructor or the copy
             * assignment operator of the vt type is not nothrow
             */
            new (this) simple_array(other);
        }

        return *this;
    }

    simple_array (simple_array&& other) noexcept: _data(other._data), _size(other._size) {
        other._data = nullptr;
        other._size = 0;
    }

    simple_array& operator= (simple_array&& other) & noexcept(std::is_nothrow_destructible_v<vt>) {
        if (this != &other) {
            this->~simple_array(); /// may throw if the destructor of the vt type is not nothrow
            /// I want to explicitly call the move constructor here.
            new (this) simple_array(std::move(other));
        }

        return *this;
    }

    vt& operator[] (const size_t i) noexcept { return _data[i]; }
    const vt& operator[] (const size_t i) const noexcept { return _data[i]; }

    size_t size () const noexcept { return _size; }

private:
    vt* _data;
    size_t _size;
};


int main () {
    simple_array<int> a(3);

    for (size_t i = 0; i < a.size(); i ++)
        a[i] = i + 1;


    simple_array<int> b(std::move(a));

    for (size_t i = 0; i < b.size(); i ++)
        std::cout << b[i] << " ";

    std::cout << std::endl;


    simple_array<int> c(5);
    c = std::move(b);

    for (size_t i = 0; i < c.size(); i ++)
        std::cout << c[i] << " ";

    std::cout << std::endl;

    return 0;
}
