// GridMap class declaration
#pragma once // prevent multiple inclusions of header

enum class TileType
{
	Wall,
	Floor,
	Water
};


// class GridMap definition
class GridMap
{
public:
	explicit GridMap(); // default constructor

	// functions to create and initialize the map
	void initialize(); // initialize the map with default tile types

	// Getters and functions to query the map	
	int getWidth() const; // get the width of the map
	int getHeight() const; // get the height of the map
	TileType getTile(int x, int y) const; // get the tile type at a specific position
	char getTileIcon(int x, int y) const; // get the character representation of the tile at a specific position

	bool isValidPosition(int x, int y) const; // check if a position is within map bounds
	bool isWalkable(int x, int y) const; // check if a tile is walkable (e.g., not a wall)

	void print() const; // print the map to the console for debugging purposes

private:
	// used for map dimensions and tile storage: system boundaries, rendering size, movement bounds
	static const int START_POS_X = 0; // minimum x-coordinate start position of the map
	static const int START_POS_Y = 0; // minimum y-coordinate start position of the map
	static const int WIDTH = 24; // fixed width of the map (49 aligns with player stats)
	static const int HEIGHT = 8; // fixed height of the map

	TileType tiles[WIDTH][HEIGHT]; // 2D array to hold tile data
};