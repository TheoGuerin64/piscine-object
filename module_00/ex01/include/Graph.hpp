#pragma once

#include <exception>
#include <string>
#include <utility>
#include <vector>

#include "Vector2.hpp"

class Graph
{
    public:

        Graph(unsigned int width, unsigned int height);
        Graph(Graph const &other);
        Graph &operator=(Graph const &other);
        ~Graph();

        void addPoint(unsigned int x, unsigned int y);
        void addLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
        void show(void) const;
        void save(char const *filename) const;
        void fromFile(std::string const &filename);

        unsigned int getWidth(void) const;
        unsigned int getHeight(void) const;

		class InvalidSizeException : public std::exception {
			public:
				char const *what(void) const throw()
                {
                    return "Invalid size";
                }
		};

        class OutOfBoundsException : public std::exception {
			public:
				char const *what(void) const throw()
                {
                    return "Out of bounds";
                }
		};

        class InvalidFileException : public std::exception {
            public:
                InvalidFileException(std::string const &filename)
                {
                    _message = "Invalid file: ";
                    _message += filename;
                }

                ~InvalidFileException() throw()
                {}

                char const *what(void) const throw()
                {
                    return _message.c_str();
                }


            private:
                std::string _message;
        };


    private:
        unsigned int _width;
        unsigned int _height;
        std::vector<Vector2> _points;
        std::vector< std::pair<Vector2, Vector2> > _lines;
};
