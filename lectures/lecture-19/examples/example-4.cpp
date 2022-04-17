#include <iostream>


int main () {
    size_t n = 5; /// amount of bytes.

    /// Raw data allocation:
    void* buffer = malloc(n);

    /// Raw data deallocation:
    free(buffer);

    return 0;
}

