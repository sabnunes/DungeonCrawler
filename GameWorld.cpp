// Member function definitions for GameWorld class

#include "GameWorld.h"

// Constructor
GameWorld::GameWorld(Random& random)
	: m_random(random), map(random)
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

const LevelDescription& GameWorld::getLevelDescription() const
{
	return levelDescription;
}

const GridMap& GameWorld::getMap() const
{
	return map;
}

Player& GameWorld::getPlayer()
{
	return player;
}

const Player& GameWorld::getPlayer() const
{
	return player;
}

PlayerMoveResult GameWorld::playerMove(const int x, const int y)
{
	PlayerMoveResult moveResult;

	// Move the player to a new position if it's valid and walkable, check for enemy collision
	Position2D posPlayer = player.getPosition();
	Position2D nextPos = posPlayer + Position2D{ x, y };

	if (isOccupiedByEnemy(nextPos))
	{
		moveResult.occupiedByEnemy = true;
		return moveResult;
	}

	// check if the tile is walkable before moving and not occupied by the enemy
	if (map.isWalkable(nextPos))
	{
		player.setPosition(Position2D{ nextPos.x, nextPos.y });
		moveResult.moved = true;
		moveResult.deltaPos = nextPos - posPlayer; // calculating change in position
	}

	return moveResult;
}

PlayerCollectedItem GameWorld::playerCollectItem()
{
	bool itemsRemaining = false;

	for (Item& item : items)
	{
		if (!item.isCollected())
		{
			itemsRemaining = true;

			if (item.getPosition() == player.getPosition())
			{
				item.collect();
				player.addInventoryItem(item);

				return { true, &item, false };
			}
		}
	}

	if (itemsRemaining)
	{
		return { false, nullptr, true };
	}
	else
	{
		return { false, nullptr, false };
	}
}

void GameWorld::playerUseItem()
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

std::vector<Enemy>& GameWorld::getEnemies()
{
	return enemies;
}

const std::vector<Enemy>& GameWorld::getEnemies() const
{
	return enemies;
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

std::vector<Item>& GameWorld::getItems()
{
	return items;
}

const std::vector<Item>& GameWorld::getItems() const
{
	return items;
}

bool GameWorld::isOccupiedByPlayer(const Position2D& position) const
{
	return position == player.getPosition();
}

bool GameWorld::isOccupiedByEnemy(const Position2D& position) const
{
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive() && position == enemy.getPosition())
		{
			return true;
		}
	}

	return false;
}

bool GameWorld::isOccupiedByItem(const Position2D& position) const
{
	for (const Item& item : items)
	{
		if (!item.isCollected() && item.getPosition() == position)
		{
			return true;
		}
	}

	return false;
}

bool GameWorld::isOccupiedByEntity(const Position2D& position) const
{
	// Map
	if (!map.isWalkable(position))
	{
		return true;
	}

	// Player
	if (isOccupiedByPlayer(player.getPosition()))
	{
		return true;
	}

	// Enemies
	if (isOccupiedByEnemy(position))
	{
		return true;
	}

	// Items
	if (isOccupiedByItem(position))
	{
		return true;
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

Position2D GameWorld::generateSpawnPosition()
{
	Position2D pos; // create a structure to hold the spawn position coordinates

	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
	do
	{
		pos.x = m_random.nextInt(1, map.getWidth() - 1);
		pos.y = m_random.nextInt(1, map.getWidth() - 1);
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

void GameWorld::spawnItems()
{
	items.clear();

	int itemCount = getLevelDescription().getItemCount();

	// Spawn all items
	for (int i = 0; i < itemCount; i++)
	{
		// New item and sets item type
		Item item(static_cast<ItemType>(m_random.nextInt(0, static_cast<int>(ItemType::count) - 1)));

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