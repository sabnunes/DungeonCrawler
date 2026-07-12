#pragma once
#include <random>

class Random
{
public:
    Random();
    explicit Random(unsigned int seed);

    //int nextInt(int min, int max);
    //bool chance(int percent);

private:
    std::mt19937 engine;

};
