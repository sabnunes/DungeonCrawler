// Direction class declaration
#pragma once

#include <array>
#include <string_view>

#include "Position2D.h"

struct Direction
{
    Position2D delta;
    std::string_view name;
};

extern const std::array<Direction, 8> directions;

std::string_view directionName(const Position2D delta);