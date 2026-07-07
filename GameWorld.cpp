// Member function definitions for GameWorld class

#include "GameWorld.h"

// Default constructor
GameWorld::GameWorld()
	: m_engine(std::random_device{}()) // Initialize the standard Mersenne Twister engine with the seed
{
}

void GameWorld::initializeLevel(int levelNumber)
{
	levelDescription = LevelDescription(levelNumber);	// Define level description for the current level
	
	map.initialize(levelDescription.getNumber());		// Initialize the map for the level

	playerSpawnPosition = generateSpawnPosition();		// Generate a random spawn position for the player
	
	spawnEnemies();	// Spawn enemies for the level
	spawnItems();	// Spawn items for the level

}

const LevelDescription& GameWorld::getLevelDescription() const
{
	return levelDescription;
}

const Position2D& GameWorld::getPlayerSpawnPosition() const
{
	return playerSpawnPosition;
}

const GridMap& GameWorld::getMap() const
{
	return map;
}

std::vector<Enemy>& GameWorld::getEnemies()
{
	return enemies;
}
const std::vector<Enemy>& GameWorld::getEnemies() const
{
	return enemies;
}


std::vector<Item>& GameWorld::getItems()
{
	return items;
}
const std::vector<Item>& GameWorld::getItems() const
{
	return items;
}

Position2D GameWorld::generateSpawnPosition()
{
	// Define the inclusive range [] for x and y; exclude walls
	std::uniform_int_distribution<int> rangeX(1, map.getWidth() - 1);
	std::uniform_int_distribution<int> rangeY(1, map.getHeight() - 1);

	Position2D pos; // create a structure to hold the spawn position coordinates

	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
	do
	{
		pos.x = rangeX(m_engine);
		pos.y = rangeY(m_engine);
	} while (!map.isWalkable(pos));

	return pos; // return the generated spawn position coordinates
}

// Returns true if the spawn position is occupied by player, enemy, or item
bool GameWorld::isSpawnPositionOccupied(const Position2D& pos) const
{
	// Map
	if (!map.isWalkable(pos))
	{
		return true;
	}

	// Player
	if (pos == getPlayerSpawnPosition()) 
	{
		return true;
	}

	// Enemies
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive() && pos == enemy.getPosition())
		{
			return true;
		}
	}

	// Items
	for (const Item& item : items)
	{
		if (!item.isCollected() && item.getPosition() == pos)
		{
			return true;
		}
	}

	return false;
}

void GameWorld::spawnEnemies()
{
	enemies.clear();

	for (EnemyType type : getLevelDescription().getEnemyTypes())
	{
		spawnEnemy(type);
	}
}

void GameWorld::spawnEnemy(EnemyType type)
{
	// New enemy
	Enemy enemy(type);

	// Create Position2D
	Position2D spawnPos;

	// Generate spawn position until position not equal to player or existing enemy position
	do
	{
		spawnPos = generateSpawnPosition();
	} while (isSpawnPositionOccupied(spawnPos));

	// Set item position to generated spawn position
	enemy.setPosition(spawnPos);

	// Add item to world items
	enemies.push_back(enemy);
}

// Spawns items
void GameWorld::spawnItems()
{
	items.clear();

	int itemCount = getLevelDescription().getItemCount();

	std::uniform_int_distribution<int> itemTypeRange(0, static_cast<int>(ItemType::count) - 1);

	// Spawn all items
	for (int i = 0; i < itemCount; i++)
	{
		// New item and sets item type
		Item item(static_cast<ItemType>(itemTypeRange(m_engine)));

		// Create Position2D for item
		Position2D spawnPos;

		// Generate spawn position for item until position not equal to player or enemy position
		do
		{
			spawnPos = generateSpawnPosition();
		} while (isSpawnPositionOccupied(spawnPos));

		// Set item position to generated spawn position
		item.setPosition(spawnPos);

		// Add item to world items
		items.push_back(item);
	}
}

bool GameWorld::isOccupiedByEnemy(const Position2D& p) const
{
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive() && p == enemy.getPosition())
		{
			return true;
		}
	}

	return false;
}

bool GameWorld::isOccupiedByEntity(const Position2D& pos, const Player& player) const
{
	// Map
	if (!map.isWalkable(pos))
	{
		return true;
	}

	// Player
	if (pos == player.getPosition())
	{
		return true;
	}

	// Enemies
	for (const Enemy& enemy : enemies)
	{
		if (isOccupiedByEnemy(pos))
		{
			return true;
		}
	}

	// Items
	for (const Item& item : items)
	{
		if (!item.isCollected() && item.getPosition() == pos)
		{
			return true;
		}
	}

	return false;
}

bool GameWorld::isEnemyAdjacentToPlayer(const Enemy& enemy, const Position2D& playerPos) const
{
	// Check all adjacent positions around the player for the live enemy's position
	for (int x = -1; x <= 1; x++) 
	{
		for (int y = -1; y <= 1; y++)
		{
			Position2D adjacentPos = Position2D{ playerPos.x + x, playerPos.y + y };

			if (!(x == 0 && y == 0) && enemy.isAlive() && adjacentPos == enemy.getPosition())
			{
				return true;
			}
		}
	}

	return false;
}

bool GameWorld::areEnemiesAdjacentToPlayer(const Position2D& playerPos) const
{

	for (const Enemy& enemy : enemies)
	{
		if (isEnemyAdjacentToPlayer(enemy, playerPos))
		{
			return true;
		}
	}

	return false;
}

bool GameWorld::areEnemiesAlive() const
{
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive())
		{
			return true;
		}
	}

	return false;
}
