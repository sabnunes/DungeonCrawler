// GameWorld class declaration

#pragma once
#include <vector>
#include <random>
#include "GridMap.h"
#include "Position2D.h"
#include "LevelDescription.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"


class GameWorld
{
public:
	GameWorld(); // default constructor

    void initializeLevel(int levelNumber); // initialize the game world with a specific level

    const LevelDescription& getLevelDescription() const;
	//const Position2D& getPlayerSpawnPosition() const;

    // Map
	//GridMap& getMap();
	const GridMap& getMap() const;

    // Player
    const Position2D& getPlayerSpawnPosition() const;
    //Player& getPlayer();
    //const Player& getPlayer() const;

    // Enemies
//    //Enemy& getEnemy() const;
    std::vector<Enemy>& getEnemies();
    const std::vector<Enemy>& getEnemies() const;

    // Items
	//Item& getItem() const;
	std::vector<Item>& getItems();
	const std::vector<Item>& getItems() const;

    // Occupancy functions
	bool isOccupiedByEnemy(const Position2D& position) const;   // returns if position is occupied by enemy
	bool isOccupiedByEntity(const Position2D& position, const Player& player) const;    // returns if position occupied by player, enemy, or item

    // Adjacency functions
    bool isEnemyAdjacentToPlayer(const Enemy& enemy, const Position2D& playerPosition) const; // returns if enemy is adjacent to player
    bool areEnemiesAdjacentToPlayer(const Position2D& playerPosition) const; // returns if any enemy adjacent to player

    bool areEnemiesAlive() const;
    //void resetGameWorld();

private:
    std::mt19937 m_engine;	// Obtain a random seed from the hardware

    LevelDescription levelDescription; // definition for the current level
	GridMap map; // the game map

    //Player player;
    Position2D playerSpawnPosition;

    std::vector<Enemy> enemies;
    std::vector<Item> items;


	Position2D generateSpawnPosition(); // returns a random spawn position for the player
    
    bool isSpawnPositionOccupied(const Position2D& position) const;

    void spawnEnemies();
    void spawnEnemy(EnemyType type);
    void spawnItems();
    
};

