// Random class declaration
#pragma once
#include <random>

class Random
{
public:
    Random();
    explicit Random(unsigned int seed); // parameterized constructor with seed

    int nextInt(int min, int max);      // returns a random int within a range
    bool chance(int percent);           // return if random is within a percentage range

    unsigned int getSeed() const;       // get game seed
    void setSeed(unsigned int seed);    // set game seed

private:
    unsigned int m_seed;                // game seed
    std::mt19937 m_engine;              // initializing engine

};
