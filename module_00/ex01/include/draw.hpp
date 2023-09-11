#pragma once

#include <string>
#include <vector>

#include "png.hpp"

void drawPoint(std::vector<PNG::Byte> &data, int width, int height, int x, int y, bool isLine = false);
void drawPoint(std::vector<std::string> &data, int width, int height, int x, int y, bool isLine = false);

// Bresenham's line algorithm
void drawLine(std::vector<PNG::Byte> &data, int width, int height, int x1, int y1, int x2, int y2);
void drawLine(std::vector<std::string> &data, int width, int height, int x1, int y1, int x2, int y2);
