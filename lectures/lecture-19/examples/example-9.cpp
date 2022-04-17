#include <iostream>


struct point {
    point (double x, double y): _x(x), _y(y) {
        std::cout << "Point (" << _x << ", " << _y << ") constructed at " << this << std::endl;
    }

    ~point () {
        std::cout << "Point (" << _x << ", " << _y << ") at " << this << " destructed" << std::endl;
    }

    point (const point& other): _x(other._x), _y(other._y) {
        std::cout << "Point copy-constructed at " << this << std::endl;
    }

    /// Common implementation of assignment operator
    point& operator= (const point& other) {
        if (this != &other) {
            /// Want to destruct the current object first
            this->~point();
            /// Want to construct the object again using the copy constructor
            new (this) point(other);
        }

        return *this;
    }

private:
    double _x, _y;
};

struct A {};

int main () {
    point first(2., 3.);
    point second(4., 5.);

    first = second;
}

