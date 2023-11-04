#pragma once

#include "Tool.hpp"

class Hammer : public Tool
{
    public:
        Hammer(void);
        ~Hammer();

        virtual void use(void);


    private:
        Hammer(Hammer const &other); // delete
        Hammer &operator=(Hammer const &other); // delete
};
