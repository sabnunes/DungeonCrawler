// GridMap class declaration
#pragma once // prevent multiple inclusions of header
#include <random>
#include "Position2D.h"

enum class TileType
{
	Wall,
	Floor,
	Water,
	Tree,
	Grass,
	Rock
};

// class GridMap definition
class GridMap
{
public:
	GridMap(); // default constructor

	void initialize(int level); // initialize the map with default tile types

	// Getters and functions to query the map	
	int getWidth() const; // get the width of the map
	int getHeight() const; // get the height of the map
	TileType getTile(int x, int y) const; // get the tile type at a specific position
	char getTileIcon(int x, int y) const; // get the character representation of the tile at a specific position

	bool isValidPosition(int x, int y) const; // check if a position is within map bounds
	bool isWalkable(int x, int y) const; // check if a tile is walkable (e.g., not a wall)
	bool isWalkable(const Position2D& pos) const; // overloaded fn used in Game class

private:
	// used for map dimensions and tile storage: system boundaries, rendering size, movement bounds
	static constexpr int START_POS_X = 0; // minimum x-coordinate start position of the map
	static constexpr int START_POS_Y = 0; // minimum y-coordinate start position of the map
	static constexpr int WIDTH = 31; // fixed width of the map (49 aligns with player stats)
	static constexpr int HEIGHT = 11; // fixed height of the map

	void generateLevelBorders(); // initialize the map with default tile types
	void applyLevelTheme(int level); // initialize the map with default tile types

	TileType tiles[WIDTH][HEIGHT]; // 2D array to hold tile data

	std::mt19937 m_engine;	// Obtain a random seed from the hardware

	void copyTiles(TileType sourceTiles[WIDTH][HEIGHT], TileType destTiles[WIDTH][HEIGHT]);
	void spreadTile(int percentChance, TileType tileType); // generate grass patches on the map
};