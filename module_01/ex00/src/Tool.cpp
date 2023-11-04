#include <cassert>
#include <iostream>

#include "Tool.hpp"
#include "Worker.hpp"

Tool::Tool(void)
    : _worker(NULL), _numberOfUses(0)
{
    std::cout << "Tool constructor called\n";
}

Tool::~Tool()
{
    std::cout << "Tool destructor called\n";

    if (_worker != NULL)
    {
        _worker->dropTool(this);
    }
}

Tool::Tool(Tool const &other)
{
    (void)other;
    assert(true);
}

Tool &Tool::operator=(Tool const &other)
{
    (void)other;
    assert(true);
    return *this;
}
