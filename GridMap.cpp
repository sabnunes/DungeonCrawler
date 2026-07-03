// Member function definitions for GridMap class
#include <iostream>
#include "GridMap.h"
#include <random>

using namespace std;

// Constructor
GridMap::GridMap()
	: m_engine(std::random_device{}()) // Initialize the standard Mersenne Twister engine with the seed
{
} // end GridMap constructor

// Initialize the map with tile types
void GridMap::initialize(int level)
{
	generateLevelBorders();
	applyLevelTheme(level);
}

void GridMap::generateLevelBorders()
{
	for (int x = START_POS_X; x < WIDTH; x++)
	{
		for (int y = START_POS_Y; y < HEIGHT; y++)
		{
			// Set borders as walls and inner area as level tile type and floor
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


void GridMap::applyLevelTheme(int level)
{
	std::uniform_int_distribution<int> dist(1, 100);

	/*
	Theme: method (simplified icons)     

	Level 1 — Open Woodland
	Purpose : Teach movement and combat.
	Mostly open. Few obstacles.
	##############################
	#............................#
	#....^.......................#
	#.............O..............#
	#............................#
	#..........^.................#
	#......................O.....#
	#............................#
	#....O...............^.......#
	##############################

	Level 2 — Rocky Meadow
	Purpose : Introduce pathing around obstacles.
	Rocks create pockets.
	More tactical movement.
	Slimes become harder to avoid.
	##############################
	#....O......O...............##
	#.................O..........#
	#..O.............O...........#
	#........O...................#
	#..............O.............#
	#..O..................O......#
	#........O...................#
	#.....O.............O........#
	##############################
	Level 3 — Dense Forest

	Purpose : Limited movement.

	Trees begin creating corridors.

	##############################
	#^^^^.....^^^^^^......^^^^^^^#
	#^^^.......^^^^....^^....^^^^#
	#^^^^..^^..^^^^....^^....^^^^#
	#^^^^..^^........^^^^^^..^^^^#
	#^^^^^^....^^^^^^....^^..^^^^#
	#^^^^^^....^^^^^^....^^..^^^^#
	#^^....^^^^^^....^^^^^^....^^#
	#^^^^^^....^^^^^^....^^^^^^..#
	##############################

	This level feels completely different despite using only one new obstacle.

	Level 4 — Riverlands

	Purpose : Force route planning.

	Water divides the map.

	##############################
	#........~~~~~~............^.#
	#....O...~~~~~~....O.........#
	#........~~~~~~..............#
	#========~~~~~~==============#
	#........~~~~~~..............#
	#...^....~~~~~~......O.......#
	#........~~~~~~..............#
	#........~~~~~~.......^......#
	##############################

	(You could later replace = with bridges.)

	Level 5 — Sacred Grove

	Purpose : Combination of every obstacle.

	The player has to navigate around forests, rocks, and water simultaneously.

	##############################
	#^^^^^^.....~~~~....O.......##
	#^^..^^.....~~~~.............#
	#^^..^^^^........^^^^^^......#
	#....^^^^..O.....^^^^^^......#
	#..............O......^^^^...#
	#~~~~~~~....^^^^^^....^^^^...#
	#~~~~~~~....^^..^^...........#
	#....O.......^^..^^.....O....#
	##############################
	Difficulty progression
	Level	Main Feature	Challenge
	1	Open field	Learn controls
	2	Rocks	Navigation
	3	Trees	Tight corridors
	4	Water	Route planning
	5	Mixed terrain	Uses everything learned
	*/


	switch (level)
	{
	case 1: // Simple forest
		for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
		{
			for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
			{
				int roll = dist(m_engine);

				// Grass seed
				if (roll == 1)
				{
					tiles[x][y] = TileType::Grass;
				}

				// Tree
				if (roll == 2 || roll == 3)
				{
					tiles[x][y] = TileType::Tree;
				}

				// Rock
				if (roll == 4)
				{
					tiles[x][y] = TileType::Rock;
				}
			}
		}
		growGrass(80);
		break;
	case 2: // Rocky Meadow
		for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
		{
			for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
			{
				int roll = dist(m_engine);

				// Grass seed
				if (roll == 1) 
				{
					// set initial tile to grass
					tiles[x][y] = TileType::Grass;
				}

				// Tree
				if (roll == 2 || roll == 3)
				{
					tiles[x][y] = TileType::Tree; 
				}

				// Rock
				if (roll >= 4 && roll <=9) 
				{
					tiles[x][y] = TileType::Rock; 
				}
			}
		}

		// Grow grass organically
		growGrass(80);
		growGrass(35);
		break;
	case 3: 
		// for random group of tiles in walkable
		// set tile to type
		// 20% of map but group together
		break;
	case 4:
		break;
	case 5: 
		break;
	default:
		break;
	}
}

void GridMap::growGrass(int percentChance)
{
	TileType newTiles[WIDTH][HEIGHT];

	// Copy current map to temp newTiles variable
	copyTiles(tiles, newTiles);

	std::uniform_int_distribution<int> dist(1, 100);

	// Ignore borders as walls
	for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
	{
		for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
		{
			if (tiles[x][y] != TileType::Grass)
			{
				continue; // skip non-grass tiles
			}

			// grow grass tiles organically
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0)
					{
						continue; // skip the original tile
					}

					int newX = x + dx;
					int newY = y + dy;

					// Check if the new position is within bounds and is a floor tile
					if (newX > START_POS_X && newX < WIDTH - 1 && newY > START_POS_Y && newY < HEIGHT - 1)
					{
						if (tiles[newX][newY] == TileType::Floor)
						{
							// Random chance to grow grass
							int rollGrow = dist(m_engine);

							if (rollGrow <= percentChance) // chance to grow grass based on parameter
							{
								newTiles[newX][newY] = TileType::Grass;

								//cout << "DEBUG: Grass grew at (" << newX << ", " << newY << ") with roll " << rollGrow << " <= " << percentChance << endl;
							}
						}
					}
				}
			}
		}
	}

	// Copy new tiles back to the original map; avoids modifying the map while iterating/causing a chain reactions
	copyTiles(newTiles, tiles);
}

// Copy tiles from source to destination
void GridMap::copyTiles(TileType  sourceTiles[WIDTH][HEIGHT], TileType  destTiles[WIDTH][HEIGHT])
{
	for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
	{
		for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
		{
			destTiles[x][y] = sourceTiles[x][y];
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
		return '#';
	case TileType::Floor:
		return ' '; 
	case TileType::Water:
		return '~';
	case TileType::Tree:
		return '^';
	case TileType::Grass:
		return ',';
	case TileType::Rock:
		return 'o';
	//case TileType::Lava:
	//	return 'v';
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
	return isValidPosition(x, y) 
		&& getTile(x, y) != TileType::Wall 
		&& getTile(x, y) != TileType::Water
		&& getTile(x, y) != TileType::Tree
		&& getTile(x, y) != TileType::Rock;
		//&& getTile(x, y) != TileType::Lava
}