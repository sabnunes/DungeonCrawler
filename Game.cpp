// Member function definitions for Game class
#include <iostream>
#include <random>
#include <iomanip>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
{
	renderSystem.printHeader();
	renderSystem.printLegend();

	nextLevel();	
} // end Game constructor

// run the game: welcome message, process main game loop (input, update, render)
void Game::run()
{
	running = true; 

	while (running)
	{
		renderSystem.render(world, playerTurn);

		if (world.getPlayer().isAlive() && playerTurn)
		{
			input();
		}
		else if (world.areEnemiesAlive() && !playerTurn)
		{
			updateEnemies();
		}
		else
		{
			if (world.getPlayer().isAlive() && currentLevel < LevelDescription::MAX_LEVEL)
			{
				renderSystem.printNextLevel();
				nextLevel();
			}
			else
			{
				renderSystem.printGameEnd(world.getPlayer().isAlive());
				running = false;
			}
		}
	}
	renderSystem.printGoodbye();
}

// Increments level to next level and triggers level intialization
void Game::nextLevel()
{
	currentLevel++;

	world.initializeLevel(currentLevel);

	renderSystem.printLevel(world.getLevelDescription());

	playerTurn = true;
}

// Get player input and process it, e.g., move player position, update health, etc
void Game::input()
{
	// Prompt the user for input
	char input;
	cout << "Enter input: ";
	cin >> input;

	// Convert input to lowercase for case-insensitive processing
	input = tolower(input);

	if (playerTurn)
	{
		// Process and verify input for movement and quitting
		switch(input)
		{
		case 'w':
			// Move player up y--
			renderSystem.printPlayerMove(world, 0, -1);
			world.playerMove(0, -1);
			break;
		case 'a':
			// Move player left x--
			renderSystem.printPlayerMove(world, -1, 0);
			world.playerMove(-1, 0);
			break;
		case 's':
			// Move player down y++
			renderSystem.printPlayerMove(world, 0, 1);
			world.playerMove(0, 1);
			break;
		case 'd':
			// Move player right x++
			renderSystem.printPlayerMove(world, 1, 0);
			world.playerMove(1, 0);
			break;
		case 'x':
			// Attack the enemy if they are in an adjacent tile (check for enemy position relative to player position)
			playerAttack();
			break;
		case 'q':
			// Quit the game
			running = false;
			break;
		case 'e':
		{
			ItemCollected itemCollected = world.playerCollectItem();
			renderSystem.printPlayerCollectItem(itemCollected);
			break;
		}
		case 'u':
		{
			if (world.getPlayer().getInventorySize() > 0)
			{
				const Item& item = world.getPlayer().getInventoryItem();

				renderSystem.printPlayerUseItem(&item);
				world.playerUseItem();
			}
			else
			{
				renderSystem.printPlayerUseItem(nullptr);
			}
		}
		default:
			renderSystem.printInvalidInput();
			break;
		}
		cout << endl;

		playerTurn = false;
	}
}

// Update game state based on input and other factors, e.g., move enemies, check for collisions, update health, etc.
void Game::updateEnemies()
{
	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			EnemyTurnResult enemyTurnResult = enemyBehavior.takeTurn(enemy, world, combatSystem);
			renderSystem.printEnemyTurn(enemy, enemyTurnResult);
		}
	}	
	cout << endl;

	playerTurn = true;
}

// Player attacks enemy, enemy loses life if attack successful, check for enemy defeat
void Game::playerAttack()
{
	Player& player = world.getPlayer();
	Enemy* attackedEnemy = nullptr;
	CombatResult combatResult{ 0, 0 };

	bool successfulAttack = false;

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && world.isEnemyAdjacentToPlayer(enemy))
		{
			combatResult = combatSystem.attack(player, enemy);
			enemy.setStunnedState(false); // reset enemy movement pattern if attacked
			attackedEnemy = &enemy;
			successfulAttack = true;

			if (combatResult.killed)
			{
				player.modifyStrength(1); // increase player strength as a reward for defeating the enemy
			}
		}
	}

	renderSystem.printPlayerAttack(attackedEnemy, combatResult, successfulAttack);
}