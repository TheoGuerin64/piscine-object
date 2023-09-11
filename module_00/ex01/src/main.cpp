#include <cassert>
#include <cmath>
#include <iostream>

#include "Graph.hpp"
#include "Vector2.hpp"

int main(void)
{
    // Create a graph of 2000x2000 pixels with a cosine wave and save it to a file
    {
        Graph graph(2000, 2000);

        unsigned int lastY = 0;
        unsigned int y;
        for (unsigned int x = 0; x < graph.getWidth(); x++)
        {
            y = std::cos(x / 50.) * 990 + graph.getWidth() / 2;
            graph.addLine(x, lastY, x, y);
            lastY = y;
        }

        graph.save("graph.png");
    }

    // Create a smiley of 20*20 pixels
    {
        Graph graph(20, 20);

        graph.addLine(5, 5, 14, 5);
        graph.addLine(3, 7, 5, 5);
        graph.addLine(14, 5, 16, 7);

        graph.addPoint(14, 15);
        graph.addPoint(15, 16);
        graph.addPoint(16, 15);

        graph.addPoint(3, 15);
        graph.addPoint(4, 16);
        graph.addPoint(5, 15);

        graph.show();
    }

    // create a graph of 10*10 pixels from a file representing a plus
    {
        Graph graph(9, 9);

        graph.fromFile("assets/plus");
        graph.save("plus.png");
    }

    // graph from an invalid file
    {
        Graph graph(5, 5);
        try {
            graph.fromFile("assets/invalid");
            assert(false);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    // graph too small for the file
    {
        Graph graph(2, 2);
        try {
            graph.fromFile("assets/plus");
            assert(false);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    // add point out of the graph
    {
        Graph graph(5, 5);
        try {
            graph.addPoint(6, 6);
            assert(false);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    // add line out of the graph
    {
        Graph graph(5, 5);
        try {
            graph.addLine(6, 1, 0, 0);
            assert(false);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    // add line out of the graph with negative coordinates
    {
        Graph graph(5, 5);
        try {
            graph.addLine(0, 0, -1, 1);
            assert(false);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
