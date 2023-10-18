#include "Graph.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "draw.hpp"
#include "png.hpp"
#include "Vector2.hpp"

Graph::Graph(unsigned int width, unsigned int height)
    : _width(width), _height(height)
{}

Graph::Graph(Graph const &other)
    : _width(other._width), _height(other._height), _points(other._points)
{}

Graph &Graph::operator=(Graph const &other)
{
    if (this != &other)
    {
        _width = other._width;
        _height = other._height;
        _points = other._points;
    }
    return *this;
}

Graph::~Graph()
{}

void Graph::addPoint(Vector2 point)
{
    if (!point.isIntegers())
    {
        throw std::invalid_argument("Point is not integers");
    }

    // Round the points to remove the possible floating point errors
    point.round();

    if (point.x < 0 || point.x >= _width || point.y < 0 || point.y >= _height)
    {
        throw OutOfBoundsException();
    }
    _points.push_back(point);
}

void Graph::addLine(Vector2 point1, Vector2 point2)
{
    if (!point1.isIntegers())
    {
        throw std::invalid_argument("Point 1 is not integers");
    }
    else if (!point2.isIntegers())
    {
        throw std::invalid_argument("Point 2 is not integers");
    }

    // Round the points to remove the possible floating point errors
    point1.round();
    point2.round();

    if (!point1.isInRange(Vector2::ZERO, Vector2(_width - 1, _height - 1))
        || !point2.isInRange(Vector2::ZERO, Vector2(_width - 1, _height - 1)))
    {
        throw OutOfBoundsException();
    }
    _lines.push_back(std::make_pair(point1, point2));
}

inline static size_t countDigits(unsigned int number)
{
    if (number == 0)
    {
        return 1;
    }
    size_t digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

static unsigned int digitAtIndex(unsigned int value, size_t index)
{
    size_t size = countDigits(value);
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return value / static_cast<unsigned long>(pow(10, size - (index + 1))) % 10;
}

void Graph::show(void) const
{
    size_t margin_left = countDigits(_height - 1);
    size_t margin_bot = countDigits(_width - 1);

    // Initialize the grid with dots
    std::vector<std::string> lines(_height, std::string(_width, '.'));

    // Add the points
    for (std::vector<Vector2>::const_iterator it = _points.begin(); it != _points.end(); it++)
    {
        drawPoint(lines, _width, _height, it->x, it->y);
    }

    // Add the lines
    for (std::vector< std::pair<Vector2, Vector2> >::const_iterator it = _lines.begin(); it != _lines.end(); it++)
    {
        if (it->first.y > it->second.y)
        {
            drawLine(lines, _width, _height, it->second.x, it->second.y, it->first.x, it->first.y);
        }
        else
        {
            drawLine(lines, _width, _height, it->first.x, it->first.y, it->second.x, it->second.y);
        }
    }

    // Print the points and the left axis
    for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); it++)
    {
        int y = _height - 1 - (it - lines.begin());
        std::cout << std::setw(margin_left) << y << *it << std::endl;
    }

    // Print the bottom axis
    for (size_t y = 0; y < margin_bot; y++)
    {
        for (size_t x = 0; x < margin_left; x++)
        {
            std::cout << " ";
        }
        for (size_t x = 0; x < _width; x++)
        {
            try {
                std::cout << digitAtIndex(x, y);
            } catch (std::out_of_range const &e) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Graph::save(char const *filename) const
{
    assert(filename != NULL);

    // Create a white background
    std::vector<PNG::Byte> data(_width * _height * 3 + _height, 255);
    for (size_t y = 0; y < _height; y++)
    {
        data[y * _width * 3 + y] = 0;
    }

    // Add points
    for (std::vector<Vector2>::const_iterator it = _points.begin(); it != _points.end(); it++)
    {
        drawPoint(data, _width, _height, it->x, it->y);
    }

    // Add lines
    for (std::vector< std::pair<Vector2, Vector2> >::const_iterator it = _lines.begin(); it != _lines.end(); it++)
    {
        if (it->first.y > it->second.y)
        {
            drawLine(data, _width, _height, it->second.x, it->second.y, it->first.x, it->first.y);
        }
        else
        {
            drawLine(data, _width, _height, it->first.x, it->first.y, it->second.x, it->second.y);
        }
    }

    PNG::create(filename, data, _width, _height);
}

void Graph::fromFile(std::string const &filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        throw std::invalid_argument("Cannot open file");
    }

    std::string input;
    while (getline(file, input))
    {
        if (input.empty())
        {
            continue;
        }
        if (input.length() < 3)
        {
            throw InvalidFileException("A line is too short in the file");
        }

        // Check if the line contains a delimiter
        size_t delimiter = input.find("-");
        if (delimiter == std::string::npos)
        {
            throw InvalidFileException("The delimiter is missing in the file");
        }

        // Check if the values are valid
        std::stringstream ss;
        ss << input.substr(0, delimiter);
        unsigned int x;
        if (!(ss >> x) || x >= this->_width)
        {
            throw InvalidFileException("A value is not a valid positive int in the file");
        }

        ss.clear();
        ss << input.substr(delimiter + 1);
        unsigned int y;
        if (!(ss >> y) || y >= this->_height)
        {
            throw InvalidFileException("A value is not a valid positive int in the file");
        }

        this->addPoint(Vector2(x, y));
    }
}

unsigned int Graph::getWidth(void) const
{
    return _width;
}

unsigned int Graph::getHeight(void) const
{
    return _height;
}

std::vector<Vector2> const &Graph::getPoints(void) const
{
    return _points;
}

std::vector< std::pair<Vector2, Vector2> > const &Graph::getLines(void) const
{
    return _lines;
}

Graph::Graph(void)
{
    assert(false);
}
