// Game class declaration
#pragma once // prevent multiple inclusions of header 

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
		explicit Game();	// default constructor
		void run();			// runs the game

	private:
		bool running = 0;	// flag to control game loop

		void initWorld();
		void spawnPlayer();
		void spawnEnemies();
		void spawnItems();
		
		std::mt19937 m_engine; // Obtain a random seed from the hardware

		Position2D generateSpawnPos(); // returns a random spawn position

		GridMap map;	// the game map
		Player player;	// the player character
		Enemy enemy;	

		std::vector<Item> worldItems;	// world items spawned
		std::vector<Enemy> enemies;		// enemies spawns

		void input();	// get player input and process it
		void update();	// update game state based on input and other factors
		void render();	// render game state to the screen
		
		void playerMove(int x, int y);	// move the player to a new position if it's valid and walkable
		void playerAttack();			// process player attacking the enemy
		void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
		void playerUseItem();			// consumes item 
		
		void enemyMove(Enemy& enemy);	// move the player to a new position if it's valid and walkable
		void enemyAttack(Enemy enemy);	// process enemy attacking the player

		bool areEnemiesAlive() const;						// returns if any enemies are alive
		bool isEnemyAdjacentToPlayer(Enemy enemy) const;	// returns if enemy is adjacent to player
		bool isAnyEnemyAdjacentToPlayer() const;			// returns if any enemy adjacent to player
		bool isOccupied(const Position2D& pos) const;		// returns if position is occupied by player, enemy, or item
		bool isOccupiedByEnemy(const Position2D& p) const;	// returns if position is occupied by enemy

		//int calculateDamage(int attackerStrength, int defenderDefense); // calculate damage dealt based on attacker strength and defender defense

		bool playerTurn = 1;			// 1 if player turn, 0 if enemy turn
		int enemyStunnedTurnsCount = 1; // counter to track enemy stunned state

		const int ITEM_TYPE_RANGE_MIN = 0;	// min item type
		const int ITEM_TYPE_RANGE_MAX = 2;	// max item types range [0-n]
		const int ITEM_COUNT = 2;			// number of items to spawn
		const int ENEMY_COUNT = 2;			// number of enemies to spawn
		const int ENEMY_STUNNED_TURNS = 1;	// counter to track enemy stunned state
};