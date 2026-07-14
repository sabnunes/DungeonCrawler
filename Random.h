#pragma once
#include <random>

class Random
{
public:
    Random();
    explicit Random(unsigned int seed);

    int nextInt(int min, int max);
    bool chance(int percent);

    unsigned int getSeed() const;
    void setSeed(unsigned int seed);

private:
    unsigned int m_seed;
    std::mt19937 m_engine;

};
