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

	player.setPosition(generateSpawnPosition());		// Generate a random spawn position for the player
	
	spawnEnemies();	// Spawn enemies for the level
	spawnItems();	// Spawn items for the level

}

//newGame()
//{
//	player = Player();   // Reset stats to defaults
//	initializeLevel(1);
//}

const LevelDescription& GameWorld::getLevelDescription() const
{
	return levelDescription;
}

Player& GameWorld::getPlayer()
{
	return player;
}

const Player& GameWorld::getPlayer() const
{
	return player;
}

void GameWorld::playerMove(const int x, const int y)
{
	// Move the player to a new position if it's valid and walkable, check for enemy collision
	Position2D pos = player.getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (map.isWalkable(newPos) && !isOccupiedByEnemy(newPos))
	{
		player.setPosition(Position2D{ newPos.x, newPos.y });
	}
}

void GameWorld::playerPickUpItem()
{
	for (Item& item : items)
	{
		if (item.getPosition() == player.getPosition() && !item.isCollected())
		{
			item.collect();
			player.addInventoryItem(item);
			return;
		}
	}
}

void GameWorld::playerUseItem()
{
	if (player.getInventorySize() > 0)
	{
		const Item& item = player.getInventoryItem();

		switch (item.getType())
		{
		case ItemType::HealthPotion: // give player +HP
			player.modifyHealth(item.getValue());
			break;
		case ItemType::StrengthPotion: // give player +STR
			player.modifyStrength(item.getValue());
			break;
		case ItemType::DefensePotion: // give player +DEF
			player.modifyDefense(item.getValue());
			break;
		default:
			break;
		}

		player.useInventoryItem();
	}
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
	if (pos == player.getPosition()) 
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

bool GameWorld::isOccupiedByEntity(const Position2D& pos) const
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

bool GameWorld::isEnemyAdjacentToPlayer(const Enemy& enemy) const
{
	// Check all adjacent positions around the player for the live enemy's position
	for (int x = -1; x <= 1; x++) 
	{
		for (int y = -1; y <= 1; y++)
		{
			Position2D adjacentPos = Position2D{ player.getPosition().x + x, player.getPosition().y + y};

			if (!(x == 0 && y == 0) && enemy.isAlive() && adjacentPos == enemy.getPosition())
			{
				return true;
			}
		}
	}

	return false;
}

bool GameWorld::areEnemiesAdjacentToPlayer() const
{

	for (const Enemy& enemy : enemies)
	{
		if (isEnemyAdjacentToPlayer(enemy))
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
