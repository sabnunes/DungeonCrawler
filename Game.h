// Game class declaration
#pragma once 
#include <vector>
#include <string>
#include "GameWorld.h"
#include "EnemyBehavior.h"
#include "CombatSystem.h"

// class Game definition
class Game
{
	public:
		Game();	// default constructor

		void run();	// runs the game

	private:
		int currentLevel = 0;	// current level number
		bool running = false;	// flag to control game loop
		bool playerTurn = true;	// 1 if player turn, 0 if enemy turn

		void nextLevel();

		void input();			// get player input and process it
		void updateEnemies();	// update game state based on input and other factors
		void render();			// render game state to the screen

		GameWorld world;
		EnemyBehavior enemyBehavior;
		CombatSystem combatSystem;	// combat system for handling attacks and damage
		
		void playerAttack();			// process player attacking the enemy

		void printLegend();
		void printLevelName();
		void printPlayerMove(int x, int y);	
		void printPlayerPickUpItem();		
		void printPlayerUseItem();			
		void printEnemyTurnResult(Enemy& enemy, EnemyTurnResult& enemyTurnResult);	

};