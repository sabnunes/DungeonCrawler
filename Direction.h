// Direction class declaration
#pragma once

#include <array>
#include <string_view>
#include "Position2D.h"

// Structure to represent direction variables
struct Direction
{
    Position2D delta;
    std::string_view name;
};

extern const std::array<Direction, 8> directions;       // Array containing all direction and direction names

std::string_view directionName(const Position2D delta); // Returns direction name when given a position delta