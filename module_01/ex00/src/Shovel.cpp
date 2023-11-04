#include <cassert>
#include <iostream>

#include "Shovel.hpp"
#include "Tool.hpp"

Shovel::Shovel(void)
    : Tool()
{
    std::cout << "Shovel constructor called\n";
}

Shovel::~Shovel()
{
    std::cout << "Shovel destructor called\n";
}

void Shovel::use(void)
{
    std::cout << "Shovel is being used\n";
}

Shovel::Shovel(Shovel const &other)
    : Tool(other)
{}

Shovel &Shovel::operator=(Shovel const &other)
{
    Tool::operator=(other);
    return *this;
}
