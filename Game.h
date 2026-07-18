// Game class declaration: runs main game loop, input handling, and turn management
#pragma once 

#include "Random.h"
#include "GameWorld.h"
#include "EnemyBehavior.h"
#include "CombatSystem.h"
#include "RenderSystem.h"

// class Game definition
class Game
{
	public:
		Game();								// default constructor
		explicit Game(unsigned int seed);	// constructor initialized with game seed

		void run();							// runs game and processes turn taking

	private:
		Random random;					// generates a random seed that is consistent throughout the game loop

		GameWorld world;				// owns the map, entities, and game state
		CombatSystem combatSystem;		// calculates attack damage and combat outcomes
		EnemyBehavior enemyBehavior;	// controls enemy AI, movement, and decision making
		RenderSystem renderSystem;		// renders game world and player feedback

		void nextLevel();				// sets level to next level and initializes the level; resets playerTurn

		void input();					// get player input and process it
		void updateEnemies();			// update game state based enemy turn
		void playerAttack();			// process player attacking the enemy
		
		int currentLevel = 0;			// current level number
		bool running = false;			// flag to control game loop
		bool playerTurn = true;			// returns if it's the player's turn

};