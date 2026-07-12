// Game class declaration
#pragma once 
#include <vector>
#include <string>
#include "Random.h"
#include "GameWorld.h"
#include "EnemyBehavior.h"
#include "CombatSystem.h"
#include "RenderSystem.h"

// class Game definition
class Game
{
	public:
		Game();	// default constructor

		void run();	// runs the game

	private:
		Random random;

		GameWorld world;
		EnemyBehavior enemyBehavior;
		CombatSystem combatSystem;	// combat system for handling attacks and damage
		RenderSystem renderSystem;

		void nextLevel();

		void input();			// get player input and process it
		void updateEnemies();	// update game state based on input and other factors
		void playerAttack();	// process player attacking the enemy
		
		int currentLevel = 0;	// current level number
		bool running = false;	// flag to control game loop
		bool playerTurn = true;	// 1 if player turn, 0 if enemy turn

};