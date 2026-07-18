// Member-function definitions for the Random class

#include "Random.h"

Random::Random()
    : m_seed(std::random_device{}()),
    m_engine(m_seed)
{
}

Random::Random(unsigned int seed)
    : m_seed(seed),
    m_engine(seed)
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

unsigned int Random::getSeed() const
{
    return m_seed;
}

void Random::setSeed(unsigned int seed)
{
    m_seed = seed;
    m_engine.seed(seed);
}
