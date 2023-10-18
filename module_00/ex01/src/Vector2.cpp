#include <cmath>

#include "Vector2.hpp"

Vector2 const Vector2::ZERO = Vector2(0.f, 0.f);

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

void Vector2::round(void)
{
    x = roundf(x);
    y = roundf(y);
}

bool Vector2::isInRange(Vector2 const &min, Vector2 const &max) const
{
    return x >= min.x && x <= max.x && y >= min.y && y <= max.y;
}

bool Vector2::isIntegers(void) const
{
    return std::abs(x - roundf(x)) < 0.0001f && std::abs(y - roundf(y)) < 0.0001f;
}
