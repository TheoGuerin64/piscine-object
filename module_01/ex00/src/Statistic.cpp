#include <iostream>

#include "Statistic.hpp"

Statistic::Statistic(int level /* = 0 */, int exp /* = 0 */)
    : level(level), exp(exp)
{
    std::cout << "Statistic constructor called\n";
}

Statistic::Statistic(Statistic const &other)
    : level(other.level), exp(other.exp)
{
    std::cout << "Statistic copy constructor called\n";
}

Statistic &Statistic::operator=(Statistic const &other)
{
    std::cout << "Statistic assignation operator called\n";

    if (this != &other)
    {
        level = other.level;
        exp = other.exp;
    }
    return *this;
}

Statistic::~Statistic()
{
    std::cout << "Statistic destructor called\n";
}

