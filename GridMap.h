// GridMap class declaration
#pragma once 
#include "Position2D.h"
#include "Random.h"

// tile types that exist in game
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
	explicit GridMap(Random& random); // constructor

	void initialize(int level);							// initializes the map with default tile types

	// functions to query the map	
	int getWidth() const;								// returns width of the map
	int getHeight() const;								// returns  height of the map
	TileType getTile(int x, int y) const;				// returns tile type at a specific position
	char getTileIcon(const Position2D& position) const; // returns character representation of tile at a specific position

	bool isValidPosition(int x, int y) const;			// returns if position is within map bounds
	bool isWalkable(int x, int y) const;				// returns if tile is walkable (e.g., not a wall or non-traversible terrain)
	bool isWalkable(const Position2D& pos) const;		// returns if tile is walkable (e.g., not a wall); overloaded function used in Game class

private:
	Random& m_random;									// reference to random created in game class

	// used for map dimensions: system boundaries, rendering size, movement bounds
	static constexpr int START_POS_X = 0;					// minimum x-coordinate start position of the map
	static constexpr int START_POS_Y = 0;					// minimum y-coordinate start position of the map
	static constexpr int WIDTH = 31;						// fixed width of the map (49 aligns with player stats)
	static constexpr int HEIGHT = 11;						// fixed height of the map

	void generateLevelBorders();							// initialize the map with level boarder tiles
	void applyLevelTheme(int level);						// initialize the map with level theme tiles

	TileType tiles[WIDTH][HEIGHT]{};						// 2D array to hold tile data

	void copyTiles(TileType sourceTiles[WIDTH][HEIGHT], 
		TileType destTiles[WIDTH][HEIGHT]);					// copies tiles from source to dest: used when spreading tiles
	void spreadTile(int percentChance, TileType tileType);	// spread tile based on existing positions

};