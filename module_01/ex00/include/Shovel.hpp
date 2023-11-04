#pragma once

#include "Tool.hpp"

class Shovel : public Tool
{
    public:
        Shovel(void);
        ~Shovel();

        virtual void use(void);


    private:
        Shovel(Shovel const &other); // delete
        Shovel &operator=(Shovel const &other); // delete
};
