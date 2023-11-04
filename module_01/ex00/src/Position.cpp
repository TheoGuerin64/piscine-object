#include <iostream>

#include "Position.hpp"

Position::Position(int x /* = 0 */, int y /* = 0 */, int z /* = 0 */)
    : x(x), y(y), z(z)
{
    std::cout << "Position constructor called\n";
}

Position::Position(Position const &other)
    : x(other.x), y(other.y), z(other.z)
{
    std::cout << "Position copy constructor called\n";
}

Position &Position::operator=(Position const &other)
{
    std::cout << "Position assignation operator called\n";

    if (this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

Position::~Position()
{
    std::cout << "Position destructor called\n";
}
