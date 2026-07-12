#include "Random.h"

Random::Random()
    : engine(std::random_device{}())
{
}

Random::Random(unsigned int seed)
    : engine(seed)
{
}

//int nextInt(int min, int max)
//{
//    std::uniform_int_distribution<int> dist(min, max);
//    return dist(engine);
//}

//bool Random::chance(int percent)
//{
//    return nextInt(1, 100) <= percent;
//}