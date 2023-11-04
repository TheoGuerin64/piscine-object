#include <iostream>

#include "Hammer.hpp"
#include "Shovel.hpp"
#include "Worker.hpp"
#include "Workshop.hpp"

int main(void)
{
    Workshop workshop;

    Worker worker1;
    Worker worker2;

    Shovel shovel;
    Hammer hammer;

    worker1.takeTool(&shovel);
    worker1.takeTool(&hammer);

    worker1.getTool<Hammer>();

    worker2.takeTool(&shovel);
    shovel.use();
    worker2.dropTool(&shovel);

    workshop.signContract(&worker1);

    try
    {
        worker2.work();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    workshop.executeWorkDay();

    workshop.resignContract(&worker1);

    try
    {
        worker1.work();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
