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
		Enemy enemy;	// the enemy character

		std::vector<Item> worldItems;

		void input();	// get player input and process it
		void update();	// update game state based on input and other factors
		void render();	// render game state to the screen
		
		void playerMove(int x, int y);	// move the player to a new position if it's valid and walkable
		void playerAttack();			// process player attacking the enemy
		void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
		
		void enemyMove();		// move the player to a new position if it's valid and walkable
		void enemyAttack();		// process enemy attacking the player

		bool isEnemyAdjacentToPlayer() const; // check if the enemy is in an adjacent tile to the player
		bool isOccupied(const Position2D& pos) const;
		
		//int calculateDamage(int attackerStrength, int defenderDefense); // calculate damage dealt based on attacker strength and defender defense

		bool playerTurn = 1; // 1 if player turn, 0 if enemy turn
		int enemyStunnedTurnsCount = 1; // counter to track enemy stunned state

		const int ITEM_COUNT = 2;
		const int ENEMY_STUNNED_TURNS = 1; // counter to track enemy stunned state


};