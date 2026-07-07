// Game class declaration
#pragma once 
#include <vector>
#include <string>
#include "GameWorld.h"
#include "Position2D.h"
#include "EnemyBehavior.h"
#include "CombatSystem.h"

#include <random>

// class Game definition
class Game
{
	public:
		Game();	// default constructor

		void run();	// runs the game

	private:
		bool running = false;	// flag to control game loop

		void printLegend();
		void printLevelName();

		void nextLevel();

		void input();			// get player input and process it
		void updateEnemies();	// update game state based on input and other factors
		void render();			// render game state to the screen
		
		GameWorld world;
		EnemyBehavior enemyBehavior;
		CombatSystem combatSystem;	// combat system for handling attacks and damage
		
		int currentLevel = 0;	// current level number
		bool playerTurn = true;	// 1 if player turn, 0 if enemy turn
		
		// TO REMOVE - MOVE INTO COMBATSYSTEMS
		void playerAttack();			// process player attacking the enemy

		// TO REMOVE - MOVED INTO GAMEWORLD
		Player player;				// the player character
		void playerMove(int x, int y);	// move the player to a new position if it's valid and walkable
		void playerPickUpItem();		// marks item as picked up if player overlaps same position as item
		void playerUseItem();			// consumes item 
		
		// TO REMOVE - MOVED INTO GAMEWORLD
		std::mt19937 m_engine;	// Obtain a random seed from the hardware
		
		// TO REMOVE - MOVED INTO ENEMYBEHAVIOR
		void enemyMove(Enemy& enemy);		// movethe player to a new position if it's valid and walkable
		void enemyAttack(Enemy& enemy);	// process enemy attacking the player

};