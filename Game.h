// Game class declaration
#pragma once 
#include <vector>
#include <string>
#include <random>
#include "Position2D.h"
#include "GridMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

// class Game definition
class Game
{
	public:
		Game();	// default constructor
		void run();			// runs the game

	private:
		bool running = false;	// flag to control game loop

		void printLegend();
		void initLevel();
		void nextLevel();

		void input();			// get player input and process it
		void updateEnemies();	// update game state based on input and other factors
		void render();			// render game state to the screen
		
		void spawnPlayer();
		void spawnEnemies();
		void spawnEnemy(EnemyType type);
		void spawnItems();
		
		std::mt19937 m_engine;			// Obtain a random seed from the hardware
		Position2D generateSpawnPos();	// returns a random spawn position

		GridMap map;	// the game map
		Player player;	// the player character

		std::vector<Item> worldItems;	// world items spawned
		std::vector<Enemy> enemies;		// enemies spawns
		
		void playerMove(int x, int y);	// move the player to a new position if it's valid and walkable
		void playerAttack();			// process player attacking the enemy
		void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
		void playerUseItem();			// consumes item 
		
		void enemyMove(Enemy& enemy);			// move the player to a new position if it's valid and walkable
		void enemyAttack(const Enemy& enemy);	// process enemy attacking the player

		bool areEnemiesAlive() const;							// returns if any enemy is alive
		bool isLiveEnemyAdjacentToPlayer(const Enemy &enemy) const;	// returns if enemy is adjacent to player
		bool areAnyLiveEnemyAdjacentToPlayer() const;			// returns if any enemy adjacent to player
		bool isOccupied(const Position2D& pos) const;			// returns if position is occupied by player, enemy, or item
		bool isOccupiedByEnemy(const Position2D& p) const;		// returns if position is occupied by enemy

		int currentLevel = 0;	// level number
		int itemCount = 0;		// number of items to spawn

		bool playerTurn = true;			// 1 if player turn, 0 if enemy turn
		int enemyStunnedTurnsCount = 1; // counter to track enemy stunned state

		const int MAX_LEVEL = 5;			// max level
		const int ITEM_TYPE_RANGE_MIN = 0;	// min item type
		const int ITEM_TYPE_RANGE_MAX = 2;	// max item types range [0-n]
		const int ENEMY_STUNNED_TURNS = 1;	// counter to track enemy stunned state
};