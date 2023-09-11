#include "Vector2.hpp"

Vector2::Vector2(float x /* = 0.f */, float y /* = 0.f */)
    : x(x), y(y)
{}

Vector2::Vector2(Vector2 const &other)
    : x(other.x), y(other.y)
{}

Vector2 &Vector2::operator=(Vector2 const &other)
{
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Vector2::operator==(Vector2 const &other) const
{
    return x == other.x && y == other.y;
}

Vector2::~Vector2()
{}
