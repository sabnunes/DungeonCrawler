// GameWorld class declaration
#pragma once
#include <vector>
#include "Random.h"
#include "Position2D.h"
#include "GridMap.h"
#include "LevelDescription.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

struct PlayerMoveResult
{
    bool moved = false;
    bool occupiedByEnemy = false;
    Position2D deltaPos = Position2D{ 0, 0 };
};

struct PlayerCollectedItem
{
    bool collected = false;
    const Item* item = nullptr;
    bool noItemHereButItemExists = false;
};

class GameWorld
{
public:
	explicit GameWorld(Random& random); // constructor

    void initializeLevel(int levelNumber); // initialize the game world with a specific level

    const LevelDescription& getLevelDescription() const;

    // Map
	const GridMap& getMap() const;

    // Player
    Player& getPlayer();
    const Player& getPlayer() const;
    PlayerMoveResult playerMove(const int x, const int y);	// move the player to a new position if it's valid and walkable
    PlayerCollectedItem playerCollectItem();		// player collects item, marks item as collected if positions overlap, returns true if item collected
    void playerUseItem();			// consumes item 

    // Enemies
    std::vector<Enemy>& getEnemies();
    const std::vector<Enemy>& getEnemies() const;
    bool areEnemiesAlive() const;

    // Items
	std::vector<Item>& getItems();
	const std::vector<Item>& getItems() const;

    // Occupancy functions
	bool isOccupiedByEnemy(const Position2D& position) const;   // returns if position is occupied by enemy
	bool isOccupiedByEntity(const Position2D& position) const;    // returns if position occupied by player, enemy, or item

    // Adjacency functions
    bool isEnemyAdjacentToPlayer(const Enemy& enemy) const; // returns if enemy is adjacent to player
    bool areEnemiesAdjacentToPlayer() const; // returns if any enemy adjacent to player


private:
    Random& m_random;

    LevelDescription levelDescription; // definition for the current level
	GridMap map; // the game map
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Item> items;

	Position2D generateSpawnPosition(); // returns a random spawn position for the player
    
    bool isSpawnPositionOccupied(const Position2D& position) const;

    void spawnEnemies();
    void spawnEnemy(EnemyType type);
    void spawnItems();
    
};

