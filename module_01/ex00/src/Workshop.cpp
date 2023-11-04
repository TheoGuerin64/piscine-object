#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Worker.hpp"
#include "Workshop.hpp"

Workshop::Workshop(void)
{}

Workshop::~Workshop()
{}

void Workshop::signContract(Worker *worker)
{
    if (worker == NULL)
    {
        throw std::invalid_argument("worker can't be NULL");
    }

    WorkerList::iterator it = std::find(_workers.begin(), _workers.end(), worker);
    if (it != _workers.end())
    {
        throw std::invalid_argument("worker already has this workshop");
    }

    std::cout << "Worker signs a contract\n";

    worker->_workshops.push_back(this);
    _workers.push_back(worker);
}

void Workshop::resignContract(Worker *worker)
{
    if (worker == NULL)
    {
        throw std::invalid_argument("worker can't be NULL");
    }

    WorkerList::iterator worker_it = std::find(_workers.begin(), _workers.end(), worker);
    Worker::WorkshopList::iterator workshop_it = std::find(worker->_workshops.begin(), worker->_workshops.end(), this);
    if (worker_it == _workers.end() || workshop_it == worker->_workshops.end())
    {
        throw std::invalid_argument("worker doesn't have this workshop");
    }

    std::cout << "Worker resigns a contract\n";

    worker->_workshops.erase(workshop_it);
    _workers.erase(worker_it);
}

void Workshop::executeWorkDay(void)
{
    std::cout << "Workshop executes a work day\n";

    for (WorkerList::iterator it = _workers.begin(); it != _workers.end(); ++it)
    {
        (*it)->work();
    }
}

Workshop::Workshop(Workshop const &other)
{
    (void)other;
    assert(false);
}

Workshop &Workshop::operator=(Workshop const &other)
{
    (void)other;
    assert(false);
    return *this;
}
