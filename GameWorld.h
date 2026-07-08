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
    //void newGame() resetGame() resetGameWorld();

    const LevelDescription& getLevelDescription() const;
	//const Position2D& getPlayerSpawnPosition() const;

    // Map
	//GridMap& getMap();
	const GridMap& getMap() const;

    // Player
    Player& getPlayer();
    const Player& getPlayer() const;
    void playerMove(const int x, const int y);	// move the player to a new position if it's valid and walkable
    void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
    void playerUseItem();			// consumes item 

    // Enemies
//    //Enemy& getEnemy() const;
    std::vector<Enemy>& getEnemies();
    const std::vector<Enemy>& getEnemies() const;
    bool areEnemiesAlive() const;

    // Items
	//Item& getItem() const;
	std::vector<Item>& getItems();
	const std::vector<Item>& getItems() const;

    // Occupancy functions
	bool isOccupiedByEnemy(const Position2D& position) const;   // returns if position is occupied by enemy
	bool isOccupiedByEntity(const Position2D& position) const;    // returns if position occupied by player, enemy, or item

    // Adjacency functions
    bool isEnemyAdjacentToPlayer(const Enemy& enemy) const; // returns if enemy is adjacent to player
    bool areEnemiesAdjacentToPlayer() const; // returns if any enemy adjacent to player


private:
    std::mt19937 m_engine;	// Obtain a random seed from the hardware

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

