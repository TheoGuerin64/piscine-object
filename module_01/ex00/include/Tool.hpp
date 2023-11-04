#pragma once

class Tool;
class Worker;

class Tool
{
    public:
        Tool(void);
        virtual ~Tool();

        virtual void use(void) = 0;

        friend class Worker;


    protected:
        Worker *_worker;
        int _numberOfUses;

        Tool(Tool const &other); // delete
        Tool &operator=(Tool const &other); // delete
};
