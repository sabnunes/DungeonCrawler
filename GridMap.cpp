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
void GridMap::initialize(int levelNumber)
{
	generateLevelBorders();
	applyLevelTheme(levelNumber);
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

		// Spread grass organically
		spreadTile(70, TileType::Grass);
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
					tiles[x][y] = TileType::Grass;
				}

				// Rock
				if (roll >= 3 && roll <=12) 
				{
					tiles[x][y] = TileType::Rock; 
				}
			}
		}

		// Spread grass organically
		spreadTile(60, TileType::Grass);
		spreadTile(15, TileType::Grass);
		break;
	case 3: // Dense forest
	{
		int halfWidth = (WIDTH - START_POS_X) / 2;
		int halfHeight = (HEIGHT - START_POS_Y) / 2;

		// Tree
		// Create a cluster of trees in the center
		for (int i = -2; i <= 2; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (abs(i) + abs(j) <= 2)
				{
					tiles[halfWidth + i][halfHeight + j] = TileType::Tree;
				}
			}
		}

		// Create a diamond pattern of trees
		int gap = 2;
		for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
		{
			for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
			{
				if (x < halfWidth - gap || x > halfWidth + gap)
				{
					tiles[x][y] = TileType::Tree;
				}
			}

			if (y < halfHeight)
			{
				gap += 3;
			}
			else
			{
				gap -= 3;
			}
		}
	}
		break;
	case 4: // Riverlands
	{
		// Create a river flowing through the map
		int interval = 0;
		int riverOffset = 1;
		const int riverTranslation= 3;
		const int riverWidth = 6; // Width of the river

		for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
		{
			for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
			{
				if (y == HEIGHT * 6 / 10)
				{
					break;
				}
				
				if (y >= HEIGHT * 7 / 10)
				{
					x += 5;
				}

				if (riverOffset == 0)
				{
					riverOffset = 1;
				}
				else if (riverOffset == 1)
				{
					riverOffset = -1;
				}
				else
				{
					riverOffset = 0;
				}

				x = y + x + riverOffset + riverTranslation;

				for (int i = 0; i < riverWidth; i++)
				{
					tiles[x][y] = TileType::Water;
					interval++;
					x++;

				}
				if (interval == riverWidth)
				{
					interval = 0;
					break;
				}

			}
		}
		
		for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
		{
			for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
			{
				int roll = dist(m_engine);
				
				// Tree
				if (roll == 1 && tiles[x][y] != TileType::Water)
				{
					tiles[x][y] = TileType::Tree;
				}

				// Rock
				if (roll == 2 && tiles[x][y] != TileType::Water)
				{
					tiles[x][y] = TileType::Rock;
				}
			}
		}
	}

		break;
	case 5: // Sacred Grove (combines all previous themes)
		for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
		{
			for (int y = START_POS_Y + 1; y < HEIGHT - 1; y++)
			{
				int roll = dist(m_engine);

				// Grass
				if (roll == 1 || roll >= 90)
				{
					tiles[x][y] = TileType::Grass;
				}

				// Tree
				if (roll == 2)
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

		// Create a diamond pattern of trees
		{
			int gap = 2;
			for (int y = START_POS_Y + HEIGHT/2 + 2; y < HEIGHT - 1; y++)
			{
				for (int x = START_POS_X + 1; x < WIDTH - 1; x++)
				{
					if (x > WIDTH / 2 + gap)
					{
						tiles[x][y] = TileType::Water;
					}
					else if (x < WIDTH / 2 - gap && y - HEIGHT/2 > 0 )
					{
						tiles[x][y - HEIGHT / 2 -1] = TileType::Tree;
					}
				}
				gap-=2;
			}
		}

		// Spread tiles organically
		spreadTile(30, TileType::Grass);
		spreadTile(15, TileType::Water);
		break;
	default:
		break;
	}
}

void GridMap::spreadTile(int percentChance, TileType tileType)
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
			if (tiles[x][y] != tileType)
			{
				continue; // skip tiles that already hold the desired tile type
			}

			// Spread tiles organically
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0)
					{
						continue; // skip original tile
					}

					int newX = x + dx;
					int newY = y + dy;

					// Check if the new position is within bounds and is a floor tile
					if (newX > START_POS_X && newX < WIDTH - 1 && newY > START_POS_Y && newY < HEIGHT - 1)
					{
						if (tiles[newX][newY] == TileType::Floor)
						{
							// Random chance to spread the tile type to adjacent floor tiles
							int rollGrow = dist(m_engine);

							if (rollGrow <= percentChance) // chance to spread tile based on percentage chance
							{
								newTiles[newX][newY] = tileType;
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
char GridMap::getTileIcon(const Position2D& p) const
{
	switch (getTile(p.x, p.y))
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
		return '*';
	default:
		return '?'; // print unknown symbol for unhandled tile types
	}
}

// Check if a position is within map bounds and not a wall or other impassable tile
bool GridMap::isValidPosition(int x, int y) const
{
	return x >= 0 && x < getWidth() && y >= 0 && y < getHeight(); // currently only checks bounds
}

// Check if a tile is walkable (e.g., not a wall)
bool GridMap::isWalkable(int x, int y) const
{
	return isValidPosition(x, y) 
		&& getTile(x, y) != TileType::Wall 
		&& getTile(x, y) != TileType::Water
		&& getTile(x, y) != TileType::Tree
		&& getTile(x, y) != TileType::Rock;
}

bool GridMap::isWalkable(const Position2D& pos) const
{
	return isWalkable(pos.x, pos.y);
}
