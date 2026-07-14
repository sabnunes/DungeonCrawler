#include "Random.h"

Random::Random()
    : m_engine(std::random_device{}())
{
}

Random::Random(unsigned int seed)
    : m_engine(seed)
{
}

int Random::nextInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

bool Random::chance(int percent)
{
    return nextInt(1, 100) <= percent;
}