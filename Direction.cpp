// Member-function definitions for the Direction class

#include "Direction.h"

const std::array<Direction, 8> directions =
{
    Direction{{ 1,  0}, "east"},
    Direction{{-1,  0}, "west"},
    Direction{{ 0,  1}, "south"},
    Direction{{ 0, -1}, "north"},
    Direction{{ 1,  1}, "southeast"},
    Direction{{ 1, -1}, "northeast"},
    Direction{{-1,  1}, "southwest"},
    Direction{{-1, -1}, "northwest"}
};

std::string_view directionName(const Position2D delta)
{
    for (const Direction& direction : directions)
    {
        if (direction.delta == delta)
        {
            return direction.name;
        }
    }

    return "unknown";
}