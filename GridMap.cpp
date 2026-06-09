// Member function definitions for GridMap class
#include <iostream>
#include "GridMap.h"

using namespace std;

// Constructor
GridMap::GridMap()
{
} // end GridMap constructor

// Initialize the map with tile types
void GridMap::initialize()
{
	for (int y = START_POS_Y; y < HEIGHT; y++)
	{
		for (int x = START_POS_X; x < WIDTH; x++)
		{
			// Set borders as walls and inner area as floor
			if (y == START_POS_Y || y == HEIGHT - 1 || x == START_POS_X || x == WIDTH - 1)
			{
				tiles[x][y] = TileType::Wall; // Set borders as walls
			}
			else
			{
				tiles[x][y] = TileType::Floor; // Set inner area as floor
			}
		}
	}
}

// Get the height of the map
int GridMap::getWidth() const
{
	return WIDTH - START_POS_X;
}

// Get the height of the map
int GridMap::getHeight() const
{
	return HEIGHT - START_POS_Y;
}

// Get the tile type at a specific position
TileType GridMap::getTile(int x, int y) const
{
	return tiles[x][y];
}

// Get the character representation of the tile at a specific position
char GridMap::getTileIcon(int x, int y) const
{
	switch (getTile(x, y))
	{
	case TileType::Wall:
		return 'X'; // print wall symbol
	case TileType::Floor:
		return ' '; // print floor symbol
	case TileType::Water:
		return '~'; // print water symbol
	default:
		return '?'; // print unknown symbol for unhandled tile types
	}
}

// Check if a position is within map bounds and not a wall or other impassable tile
bool GridMap::isValidPosition(int x, int y) const
{
	return x >= 0 && x < getWidth() && y >= 0 && y < getHeight(); // currently only checks bounds
	// may need to check for walls or other impassable tiles in the future -- test against tile type at this position ?
}

// Check if a tile is walkable (e.g., not a wall)
bool GridMap::isWalkable(int x, int y) const
{
	return isValidPosition(x, y) && getTile(x, y) != TileType::Wall && getTile(x, y) != TileType::Water;
}

// TEMP Print the map to the console for debugging purposes
void GridMap::print() const
{
	for (int y = START_POS_Y; y < HEIGHT; y++)
	{
		for (int x = START_POS_X; x < WIDTH; x++)
		{
			switch (tiles[x][y]) 
			{
			case TileType::Wall:
				cout << "X"; // Wall
				break;
			case TileType::Floor:
				cout << " "; // Floor
				break;
			case TileType::Water:
				cout << "~"; // Water
				break;
			default:
				cout << "?"; // Unknown tile type
				break;
			}
		}
		puts(""); // New line after each row
	}
}
