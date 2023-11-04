#include <cassert>
#include <iostream>

#include "Hammer.hpp"
#include "Tool.hpp"

Hammer::Hammer(void)
    : Tool()
{
    std::cout << "Hammer constructor called\n";
}

Hammer::~Hammer()
{
    std::cout << "Hammer destructor called\n";
}

void Hammer::use(void)
{
    std::cout << "Hammer is being used\n";

    _numberOfUses++;
}

Hammer::Hammer(Hammer const &other)
    : Tool(other)
{}

Hammer &Hammer::operator=(Hammer const &other)
{
    Tool::operator=(other);
    return *this;
}
