#pragma once

struct Statistic
{
    public:
        int level;
        int exp;

        Statistic(int level = 0, int exp = 0);
        Statistic(Statistic const &other);
        Statistic &operator=(Statistic const &other);
        ~Statistic();
};

