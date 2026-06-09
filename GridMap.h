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
	//void create(); // create a new map with specific tile types // may be needed for resetting map -> rename
	void initialize(); // initialize the map with default tile types

	// Getters and functions to query the map	
	int getWidth() const; // get the width of the map
	int getHeight() const; // get the height of the map
	TileType getTile(int x, int y) const; // get the tile type at a specific position
	char getTileIcon(int x, int y) const; // get the character representation of the tile at a specific position

	bool isValidPosition(int x, int y) const; // check if a position is within map bounds
	bool isWalkable(int x, int y) const; // check if a tile is walkable (e.g., not a wall)

	//// functions to modify the map
	//void setTile(int x, int y, TileType type); // set the tile type at a specific position
	//void placeObject(int x, int y); // place an object on the map at a specific position (e.g., a treasure or enemy)
	//void updateTile(int x, int y, TileType newType); // update the tile type at a specific position (e.g., change floor to water)

	void print() const; // print the map to the console for debugging purposes

private:
	// used for map dimensions and tile storage: system boundaries, rendering size, movement bounds
	static const int START_POS_X = 0; // minimum x-coordinate start position of the map
	static const int START_POS_Y = 0; // minimum y-coordinate start position of the map
	static const int WIDTH = 41; // fixed width of the map
	static const int HEIGHT = 12; // fixed height of the map

	TileType tiles[WIDTH][HEIGHT]; // 2D array to hold tile data
};