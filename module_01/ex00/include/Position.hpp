#pragma once

struct Position
{
    public:
        int x;
        int y;
        int z;

        Position(int x = 0, int y = 0, int z = 0);
        Position(Position const &other);
        Position &operator=(Position const &other);
        ~Position();
};

