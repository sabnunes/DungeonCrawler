// Position2D class declaration
#pragma once

// Structure to represent a 2D position on the map
struct Position2D
{
	int x; // x-coordinate position
	int y; // y-coordinate position

	// Equality operator to compare two Position2D objects
    bool operator==(const Position2D& other) const
    {
        return x == other.x && y == other.y;
    }
};