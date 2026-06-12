// Game class declaration
#pragma once // prevent multiple inclusions of header 

#include <string>
#include "Position2D.h"
#include "GridMap.h"
#include "Player.h"
#include "Enemy.h"

// class Game definition
class Game
{
	public:
	
		explicit Game();	// default constructor
		void run();			// runs the game

	private:
		bool running = 0;	// flag to control game loop

		GridMap map;	// the game map
		Player player;	// the player character
		Enemy enemy;	// the enemy character

		Position2D generateSpawnPos(); // returns a random spawn position

		void input();			// get player input and process it
		void update();			// update game state based on input and other factors
		void render() const;	// render game state to the screen
		
		int enemyMoveCounter = 0; // counter to track enemy movement pattern and behavior
		void movePlayer(int x, int y);	// move the player to a new position if it's valid and walkable
		void moveEnemy();	// move the player to a new position if it's valid and walkable

		bool isEnemyAdjacentToPlayer(); // check if the enemy is in an adjacent tile to the player

		void playerAttack();	// process player attacking the enemy
		void enemyAttack();		// process enemy attacking the player
		//int calculateDamage(int attackerStrength, int defenderDefense); // calculate damage dealt based on attacker strength and defender defense

};