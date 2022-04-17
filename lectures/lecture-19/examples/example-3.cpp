#include <iostream>


/// Simple class that couts it's construction and destruction
struct logger {
    logger () { std::cout << "Object constructed at " << this << std::endl; }
    ~logger () { std::cout << "Object at " << this << " destructed" << std::endl; }

    logger (const int x, const double y) {
        std::cout << "Object constructed with args " << x << ", " << y << " at " << this << std::endl;
    }
};

int main () {
    std::cout << "Let's use operator new in order to allocate 3 logger objects" << std::endl;
    logger* objs = new logger[3];
    std:: cout << "Let's use operator delete in order to deallocate all logger objects" << std::endl;
    delete[] objs;
    return 0;
}

