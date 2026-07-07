// Game class declaration
#pragma once 
#include <vector>
#include <string>
#include "GameWorld.h"
#include "Position2D.h"
#include "GridMap.h"
#include "Player.h"
#include "EnemyBehavior.h"
#include "CombatSystem.h"

#include <random>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "LevelDescription.h"

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
		
		// Will become
		GameWorld world;
		Player player;	// the player character
		EnemyBehavior enemyBehavior;
		CombatSystem combatSystem;	// combat system for handling attacks and damage
		
		void playerMove(int x, int y);	// move the player to a new position if it's valid and walkable
		void playerAttack();			// process player attacking the enemy
		void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
		void playerUseItem();			// consumes item 

		int currentLevel = 0;	// level number

		bool playerTurn = true;			// 1 if player turn, 0 if enemy turn
		
		// TO REMOVE - MOVED INTO GAMEWORLD
		std::mt19937 m_engine;	// Obtain a random seed from the hardware
		void spawnPlayer();
		void spawnEnemies();
		void spawnEnemy(EnemyType type);
		void spawnItems();
		Position2D generateSpawnPos();	// returns a random spawn position
		LevelDescription levelDesc; // levelDesc definition for the current levelDesc
		GridMap map;	// the game map
		std::vector<Item> worldItems;	// world items spawned
		std::vector<Enemy> enemies;		// enemies spawns
		
		// TO REMOVE - MOVED INTO ENEMYBEHAVIOR
		void enemyMove(Enemy& enemy);		// movethe player to a new position if it's valid and walkable
		void enemyAttack(Enemy& enemy);	// process enemy attacking the player

		// TO REMOVE - MOVED INTO GAMEWORLD
		bool areEnemiesAlive() const;							// returns if any enemy is alive
		bool isOccupied(const Position2D& pos) const;			// returns if position is occupied by player, enemy, or item
		bool isOccupiedByEnemy(const Position2D& p) const;		// returns if position is occupied by enemy
		bool isLiveEnemyAdjacentToPlayer(const Enemy& enemy) const;	// returns if enemy is adjacent to player
		bool areAnyLiveEnemyAdjacentToPlayer() const;			// returns if any enemy adjacent to player

};