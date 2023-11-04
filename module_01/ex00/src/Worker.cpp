#include <algorithm>
#include <cassert>
#include <iostream>

#include "Tool.hpp"
#include "Worker.hpp"

Worker::Worker(Position const &coordonnee /* = Position() */, Statistic const &stat /* = Statistic() */)
    : _coordonnee(coordonnee), _stat(stat)
{
    std::cout << "Worker constructor called\n";
}

Worker::~Worker()
{
    std::cout << "Worker destructor called\n";

    for (ToolList::iterator it = _tools.begin(); it != _tools.end(); it++)
    {
        (*it)->_worker = NULL;
    }
}

void Worker::takeTool(Tool *tool)
{
    if (tool == NULL)
    {
        throw std::invalid_argument("tool can't be NULL");
    }

    if (tool->_worker != NULL)
    {
        tool->_worker->dropTool(tool);
    }

    std::cout << "Worker takes a tool\n";

    tool->_worker = this;
    _tools.push_back(tool);
}

void Worker::dropTool(Tool *tool)
{
    if (tool == NULL)
    {
        throw std::invalid_argument("tool can't be NULL");
    }

    ToolList::iterator it = std::find(_tools.begin(), _tools.end(), tool);
    if (it == _tools.end())
    {
        throw std::invalid_argument("worker doesn't have this tool");
    }

    std::cout << "Worker drops a tool\n";

    tool->_worker = NULL;
    _tools.erase(it);
}

std::vector<Tool *> const &Worker::getTools(void) const
{
    std::cout << "Worker gets tools\n";

    return _tools;
}

void Worker::work(void)
{
    if (_workshops.empty())
    {
        throw std::invalid_argument("worker doesn't have any workshop");
    }

    std::cout << "Worker works\n";
}

Worker::Worker(Worker const &other)
{
    (void)other;
    assert(true);
}

Worker &Worker::operator=(Worker const &other)
{
    (void)other;
    assert(true);
    return *this;
}
