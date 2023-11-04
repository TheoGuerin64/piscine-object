#pragma once

#include <vector>

class Tool;
class Worker;
class Workshop;

#include "Position.hpp"
#include "Statistic.hpp"

class Worker {
    public:
        Worker(Position const &coordonnee = Position(), Statistic const &stat = Statistic());
        ~Worker();

        void takeTool(Tool *tool);
        void dropTool(Tool *tool);
        std::vector<Tool *> const &getTools(void) const;
        void work(void);

        template <class T>
        Tool *getTool() const
        {
            for (ToolList::const_iterator it = _tools.begin(); it != _tools.end(); it++)
            {
                if (dynamic_cast<T *>(*it) != NULL)
                {
                    return *it;
                }
            }
            return NULL;
        }

        friend class Workshop;


    private:
        typedef std::vector<Tool *> ToolList;
        typedef std::vector<Workshop *> WorkshopList;

        ToolList _tools;
        Position _coordonnee;
        Statistic _stat;
        WorkshopList _workshops;

        Worker(Worker const &other); // delete
        Worker &operator=(Worker const &other); // delete

};
