#include "zlib.h"
#include <cassert>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "png.hpp"

inline static Byte extractByte(int value, int index)
{
    return static_cast<Byte>(value >> (index * 8));
}

std::vector<Byte> PNG::compressBytes(Byte const *data, size_t size)
{
    std::vector<Byte> compressed;

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    int ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    assert(ret == Z_OK);

    stream.avail_in = size;
    stream.next_in = const_cast<Bytef *>(data);

    do
    {
        Byte out[1024];
        stream.avail_out = 1024;
        stream.next_out = out;

        ret = deflate(&stream, Z_FINISH);
        assert(ret != Z_STREAM_ERROR);

        compressed.insert(compressed.end(), out, out + 1024 - stream.avail_out);
    } while (stream.avail_out == 0);

    deflateEnd(&stream);

    return compressed;
}

void PNG::addChunk(std::vector<Byte> &file, Byte const *data, size_t size, char const *type)
{
    std::vector<Byte> chunk;
    chunk.reserve(size + 12);

    // Length
    chunk.push_back(extractByte(size, 3));
    chunk.push_back(extractByte(size, 2));
    chunk.push_back(extractByte(size, 1));
    chunk.push_back(extractByte(size, 0));

    // Type
    chunk.insert(chunk.end(), type, type + 4);

    // Data
    chunk.insert(chunk.end(), data, data + size);

    // CRC
    unsigned long crc = crc32(0, chunk.data() + 4, chunk.size() - 4);
    chunk.push_back(extractByte(crc, 3));
    chunk.push_back(extractByte(crc, 2));
    chunk.push_back(extractByte(crc, 1));
    chunk.push_back(extractByte(crc, 0));

    file.insert(file.end(), chunk.begin(), chunk.end());
}

void PNG::create(char const *filename, std::vector<Byte> const &pixels, size_t width, size_t height)
{
    std::ofstream image(filename, std::fstream::binary | std::fstream::trunc);
    if (!image.is_open())
    {
        throw std::invalid_argument("Cannot open file");
    }

    std::vector<Byte> file;
    file.insert(file.begin(), signature, signature + sizeof(signature));

    Byte ihdrData[] = {
        extractByte(width, 3), extractByte(width, 2), extractByte(width, 1), extractByte(width, 0), // Width
        extractByte(height, 3), extractByte(height, 2), extractByte(height, 1), extractByte(height, 0), // Width
        0x08, // Bit depth (8)
        0x02, // Color type (true color)
        0x00, // Compression method (deflate)
        0x00, // Filter method (None)
        0x00 // Interlace method (no interlace)
    };
    addChunk(file, ihdrData, sizeof(ihdrData), "IHDR");

    std::vector<Byte> compressedPixels = compressBytes(pixels.data(), pixels.size());
    addChunk(file, compressedPixels.data(), compressedPixels.size(), "IDAT");

    Byte iendData[] = {};
    addChunk(file, iendData, sizeof(iendData), "IEND");

    image.write(reinterpret_cast<char*>(file.data()), file.size());
    image.close();
}
