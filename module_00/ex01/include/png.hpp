#pragma once

#include <cstddef>
#include <vector>

namespace PNG
{
    typedef unsigned char Byte;

    Byte const signature[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

    std::vector<Byte> compressBytes(Byte const *data, size_t size);
    void addChunk(std::vector<Byte> &file, Byte const *data, size_t size, char const *type);
    void create(char const *filename, std::vector<Byte> const &pixels, size_t width, size_t height);
    std::vector<Byte> read(char const *filename);
};
