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
	char playerInput;
	cout << "Enter input: ";
	cin >> playerInput;

	// Convert input to lowercase for case-insensitive processing
	int input = tolower(playerInput);

	if (playerTurn)
	{
		// Process and verify input for movement and quitting
		switch(input)
		{
		case 'w': // Move player up y--
		{
			PlayerMoveResult moveResult = world.playerMove(0, -1);
			renderSystem.printPlayerMove(world, moveResult);
			break;
		}
		case 'a': // Move player left x--
		{
			PlayerMoveResult moveResult = world.playerMove(-1, 0);
			renderSystem.printPlayerMove(world, moveResult);
			break;
		}
		case 's': // Move player down y++
		{
			PlayerMoveResult moveResult = world.playerMove(0, 1);
			renderSystem.printPlayerMove(world, moveResult);
			break;
		}
		case 'd': // Move player right x++
		{
			PlayerMoveResult moveResult = world.playerMove(1, 0);
			renderSystem.printPlayerMove(world, moveResult);
			break;
		}
		case 'x': // Attack the enemy if adjacent
			playerAttack();
			break;
		case 'q': // Quit the game
			running = false;
			break;
		case 'e': // Collect item
		{
			PlayerCollectedItem itemCollected = world.playerCollectItem();
			renderSystem.printPlayerCollectItem(itemCollected);
			break;
		}
		case 'u': // Use Item
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
			break;
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
			if (!world.getPlayer().isAlive())
			{
				break;
			}
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
			break;
		}
	}

	renderSystem.printPlayerAttack(attackedEnemy, combatResult, successfulAttack);
}