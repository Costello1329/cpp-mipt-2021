#include <iostream>


int main () {
    size_t n = 7; /// amount of bytes.

    /// Raw data allocation:
    char* buffer = new char[n];

    /// Raw data deallocation:
    delete[] buffer;

    return 0;
}

