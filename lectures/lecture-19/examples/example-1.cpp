#include <iostream>


/// Simple class that couts it's construction and destruction
struct logger {
    logger () { std::cout << "Object constructed at " << this << std::endl; }
    ~logger () { std::cout << "Object at " << this << " destructed" << std::endl; }
};

int main () {
    std::cout << "Let's use operator new in order to allocate a logger object" << std::endl;
    logger* obj = new logger();
    std:: cout << "Let's use operator delete in order to deallocate a logger object" << std::endl;
    delete obj;
    return 0;
}

