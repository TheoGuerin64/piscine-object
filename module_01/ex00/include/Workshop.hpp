#pragma once

#include <string>
#include <vector>

class Workshop;
class Worker;

class Workshop {
    public:
        Workshop(void);
        ~Workshop();

        void signContract(Worker *worker);
        void resignContract(Worker *worker);
        void executeWorkDay(void);


    private:
        typedef std::vector<Worker *> WorkerList;

        WorkerList _workers;

        Workshop(Workshop const &other); // delete
        Workshop &operator=(Workshop const &other); // delete
};
