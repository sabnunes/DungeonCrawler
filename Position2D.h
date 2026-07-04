// Position2D class declaration
#pragma once

// Structure to represent a 2D position on the map
struct Position2D
{
	int x = 1; // x-coordinate position
	int y = 1; // y-coordinate position

	// Equality operator to compare two Position2D objects
    bool operator==(const Position2D& other) const
    {
        return x == other.x && y == other.y;
    }
};