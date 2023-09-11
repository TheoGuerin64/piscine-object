#include "draw.hpp"

#include <cmath>
#include <string>
#include <vector>

#include "png.hpp"

inline void drawPoint(std::vector<PNG::Byte> &data, int width, int height, int x, int y, bool isLine /* = false */)
{
    (void)height;
    data[y * width * 3 + y + x * 3 + 1] = isLine ? 255 : 0;
    data[y * width * 3 + y + x * 3 + 2] = 0;
    data[y * width * 3 + y + x * 3 + 3] = 0;
}

inline void drawPoint(std::vector<std::string> &data, int width, int height, int x, int y, bool isLine /* = false */)
{
    (void)width;
    data[height - y - 1][x] = isLine ? 'o' : '0';
}

inline static void drawLineLow(std::vector<PNG::Byte> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y1;

    for (int x = x1; x <= x2; x++)
    {
        drawPoint(data, width, height, x, y, true);
        if (D > 0)
        {
            y += yi;
            D += 2 * (dy - dx);
        }
        else
        {
            D += 2 * dy;
        }
    }
}

inline static void drawLineHigh(std::vector<PNG::Byte> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x1;

    for (int y = y1; y <= y2; y++)
    {
        drawPoint(data, width, height, x, y, true);
        if (D > 0)
        {
            x += xi;
            D += 2 * (dx - dy);
        }
        else
        {
            D += 2 * dx;
        }
    }
}

void drawLine(std::vector<PNG::Byte> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    if (std::abs(y2 - y1) < std::abs(x2 - x1))
    {
        if (x1 > x2)
        {
            drawLineLow(data, width, height, x2, y2, x1, y1);
        }
        else
        {
            drawLineLow(data, width, height, x1, y1, x2, y2);
        }
    }
    else
    {
        if (y1 > y2)
        {
            drawLineHigh(data, width, height, x2, y2, x1, y1);
        }
        else
        {
            drawLineHigh(data, width, height, x1, y1, x2, y2);
        }
    }
}

inline static void drawLineLow(std::vector<std::string> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y1;

    for (int x = x1; x <= x2; x++)
    {
        drawPoint(data, width, height, x, y, true);
        if (D > 0)
        {
            y += yi;
            D += 2 * (dy - dx);
        }
        else
        {
            D += 2 * dy;
        }
    }
}

inline static void drawLineHigh(std::vector<std::string> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x1;

    for (int y = y1; y <= y2; y++)
    {
        drawPoint(data, width, height, x, y, true);
        if (D > 0)
        {
            x += xi;
            D += 2 * (dx - dy);
        }
        else
        {
            D += 2 * dx;
        }
    }
}

void drawLine(std::vector<std::string> &data, int width, int height, int x1, int y1, int x2, int y2)
{
    if (std::abs(y2 - y1) < std::abs(x2 - x1))
    {
        if (x1 > x2)
        {
            drawLineLow(data, width, height, x2, y2, x1, y1);
        }
        else
        {
            drawLineLow(data, width, height, x1, y1, x2, y2);
        }
    }
    else
    {
        if (y1 > y2)
        {
            drawLineHigh(data, width, height, x2, y2, x1, y1);
        }
        else
        {
            drawLineHigh(data, width, height, x1, y1, x2, y2);
        }
    }
}
