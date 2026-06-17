// Member function definitions for Game class
#include <iostream>
#include <random>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
{
	map.initialize();// initialize the map

	Position2D spawnPos_Player; // create a structure to hold the spawn position coordinates for the player
	Position2D spawnPos_Enemy; // create a structure to hold the spawn position coordinates for the enemy

	do
	{
		spawnPos_Player = generateSpawnPos(); // generate a random spawn position for the player
		spawnPos_Enemy = generateSpawnPos(); // generate a random spawn position for the enemy
	} while (spawnPos_Player == spawnPos_Enemy); // regenerate if player and enemy spawn positions are identical to avoid overlap

	// Set the player and enemy's position to the generated spawn position
	player.setPosition(spawnPos_Player.x, spawnPos_Player.y);
	enemy.setPosition(spawnPos_Enemy.x, spawnPos_Enemy.y);


} // end Game constructor

// run the game: welcome message, process main game loop (input, update, render)
void Game::run()
{
	cout << "Welcome to DUNGEON CRAWLER\n" << endl;
	//cout << "Menu :\n1. Start Game\n2. Quit\nEnter your choice: ";

	running = true; // set running flag to true to start the game loop

	while (running)
	{
		render();
		if (player.isAlive() && playerTurn)
		{
			input();
		}
		else if (enemy.isAlive() && !playerTurn)
		{
			update();
		}
		else
		{
			printf("%s\n", player.isAlive() ? "You've defeated all enemies! You win!" : "You are dead. Game over.");
			running = 0;
		}
	}
	cout << "Thanks for playing!" << endl;
} // end function run

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
			case 'p':
				// Move player up y--
				playerMove(0, -1);
				break;
			case 'a':
			case 'l':
				// Move player left x--
				playerMove(-1, 0);
				break;
			case 's':
			case ';':
				// Move player down y++
				playerMove(0, 1);
				break;
			case 'd':
			case '\'':
				// Move player right x++
				playerMove(1, 0);
				break;
			case 'x':
			case '.':
				// Attack the enemy if they are in an adjacent tile (check for enemy position relative to player position)
				playerAttack();
				break;
			case 'q':
			case '[':
				// Quit the game
				running = false;
				break;
			default:
				cout << "Invalid input. Use WASD keys to move, Q to quit." << endl;
				break;
		}
		playerTurn = 0;
	}
}

// Update game state based on input and other factors, e.g., move enemies, check for collisions, update health, etc., 
// check for win/loss conditions
void Game::update()
{
	//cout << "update\n";
	//Enemy moves
	//Poison damage
	//Health regeneration
	//Cooldowns
	//Turn processing
	//Projectile movement
	//Loot despawning


	if (!enemy.isAlive())
	{
		return;
	}

	if (isEnemyAdjacentToPlayer())
	{
		enemyAttack();
	}
	else
	{
		enemyMove();
	}
	puts(""); // New line after update for better readability
	playerTurn = 1;
}

// Render game state to the screen,	display player health, inventory, etc., display game world, enemies, etc.
void Game::render()
{
	//printf("\nDUNGEON CRAWLER\n\n"); // top toolbar with game title and stats
	
	// Print player and enemy stats
	printf("Player | HP: %3d | STR: %2d | DEF: %2d | POS: %2d,%2d\n", 
		player.getHealth(), player.getStrength(), player.getDefense(), player.getPosition().x, player.getPosition().y);
	if (enemy.isAlive())
	{
		printf("Enemy  | HP: %3d | STR: %2d | DEF: %2d | POS: %2d,%2d\n",
			enemy.getHealth(), enemy.getStrength(), enemy.getDefense(), enemy.getPosition().x, enemy.getPosition().y);
	}
	puts(""); // New line after stats

	// Render the grid map with the player icon
	//map.print(); // debugging: print the map to the console
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++) {
			if (player.getPosition() == Position2D{ x, y } && player.isAlive())
			{
				cout << player.getIcon(); // print player icon if player is at this coordinate
			}
			else if (enemy.getPosition() == Position2D{ x, y } && enemy.isAlive())
			{
				cout << enemy.getIcon(); // print enemy icon if enemy is at this coordinate
			}
			else
			{
				cout << map.getTileIcon(x, y); // print tile icon for the current tile
			}
		}
		puts(""); // New line after each row
	}

	if (player.isAlive() && enemy.isAlive())
	{
		printf("\n%s\n", playerTurn ? "Your turn. Use WASD to move, X to attack, Q to quit." : "Enemy turn.");
		printf("Enemy adjacent to player? %s\n", isEnemyAdjacentToPlayer() ? "Yes" : "No");
	}
	puts("");
}


// Generate a random valid walkable coordinate and assign it to the player
Position2D Game::generateSpawnPos()
{
	random_device randNumGen; // Obtain a random seed from the hardware
	mt19937 randEngine(randNumGen()); // Initialize the standard Mersenne Twister engine with the seed

	// Define the inclusive range [] for x and y; exclude walls
	uniform_int_distribution<int> rangeX(1, map.getWidth() - 2);
	uniform_int_distribution<int> rangeY(1, map.getHeight() - 2);

	Position2D pos; // create a structure to hold the spawn position coordinates

	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
	do
	{
		pos.x = rangeX(randEngine);
		pos.y = rangeY(randEngine);
	} while (!map.isWalkable(pos.x, pos.y));

	return pos; // return the generated spawn position coordinates
}

// Move the player to a new position if it's valid and walkable, check for enemy collision
void Game::playerMove(int x, int y)
{
	Position2D pos = player.getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (map.isWalkable(newPos.x, newPos.y) && (!enemy.isAlive() || !(newPos == enemy.getPosition())))
	{
		player.setPosition(newPos.x, newPos.y);
		cout << "Moved " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ". ";
		/*if (enemy.isAlive() && isEnemyAdjacentToPlayer())
		{
			cout << "Enemy nearby! Use X to attack.";
		}*/
		cout << endl;
	}
	else if (enemy.isAlive() && newPos == enemy.getPosition()) // don't move if player is trying to move into the enemy's position
	{
		cout << "Cannot move there. Use X to attack or WASD to move.\n";
	}
	else // if the tile is not walkable, print a message indicating the player cannot move in that direction
	{
		cout << "Cannot move " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ", tile is not walkable.\n";
	}
}

// Enemy movement behavior and pattern
void Game::enemyMove()
{
	//enemy behavior
	// idle for 2 turns
	// begin movement pattern
	// if attacked, move away from player, resets idle/movement pattern
	
	// movement ideas: 
	// + pattern
	// - or | pattern
	// 4 squares pattern (L,R,D,U)
	// random movement
	// chance of no movement

	if (enemyStunnedTurnsCount <= ENEMY_STUNNED_TURNS)
	{
		enemyStunnedTurnsCount++;
		return;
	}
	else
	{
		random_device randNumGen; // Obtain a random seed from the hardware
		mt19937 randEngine(randNumGen()); // Initialize the standard Mersenne Twister engine with the seed

		// Define the inclusive range [] for x and y;
		uniform_int_distribution<int> range(-1, 1);

		Position2D pos; // create a structure to hold the spawn position coordinates

		// x and y coordinate variables
		int x = 0;
		int y = 0;

		// Generate random x and y coordinates for the spawn position, regenerate if not walkable
		do
		{
			x = range(randEngine);
			y = range(randEngine);
			pos.x = enemy.getPosition().x + x;
			pos.y = enemy.getPosition().y + y;
		} while (!map.isWalkable(pos.x, pos.y) || (x == 0 && y == 0));

		if (!(pos == player.getPosition()))
		{
			enemy.setPosition(pos.x, pos.y);
			printf("Enemy moved %s.\n", x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up")));
		}
		else if (pos == player.getPosition()) // check if the enemy is trying to move into the player's position
		{
			cout << "Enemy attempted move, but cannot move there - overlaps with player.\n";
		}
		else
		{
			cout << "Enemy cannot move.\n";
		}
	}
}

// Check if the enemy and player are in adjacent tiles (including diagonals)
bool Game::isEnemyAdjacentToPlayer() const
{
	// check:
	// x:-1 y:-1 upper left
	// x:-1 y: 0 left
	// x:-1 y:+1 lower left
	// x: 0 y:-1 up
	// x: 0 y:+1 down
	// x:+1 y:-1 upper right
	// x:+1 y: 0 right
	// x:+1 y:+1 lower right

	// get player and enemy positions
	Position2D playerPos = player.getPosition();
	Position2D enemyPos = enemy.getPosition();

	// Check all adjacent positions around the player for the enemy's position
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) 
		{
			if (Position2D{ playerPos.x + x, playerPos.y + y } == enemyPos) 
			{
				return true; // Enemy is adjacent to the player
			}
		}
	}

	return false;
}

// Player attacks enemy, enemy loses life if attack successful, check for enemy defeat
void Game::playerAttack()
{
	cout << "Attack enemy.\n";
	// Implement attack logic here
	if (isEnemyAdjacentToPlayer() && enemy.isAlive())
	{
		// player attacks enemy
		enemy.setHealth(enemy.getHealth() - player.getStrength());
		enemyStunnedTurnsCount = 0; // reset enemy movement pattern if attacked
		cout << "Attack successful. ";

		if (enemy.getHealth() <= 0)
		{
			cout << "Enemy is dead! Strength increased +1.\n";
			player.setStrength(player.getStrength()+1); // increase player strength as a reward for defeating the enemy
			// handle enemy defeat drop loot etc
		}
		else
		{
			cout << "Enemy lost " << player.getStrength() << " HP.\n";
			cout << "Enemy preparing counterattack.\n";
		}
	}
	else
	{
		cout << "No enemy in range. Invalid move.\n";
	}
}

// Enemy attacks player, player loses life if attack successful, check for player defeat
void Game::enemyAttack()
{
	cout << "Enemy attack.\n";

	if (isEnemyAdjacentToPlayer())
	{
		// enemy attacks player
		player.setHealth(player.getHealth() - enemy.getStrength());
		cout << "Enemy attack successful. You lost " << enemy.getStrength() << " HP.\n";
		if (player.getHealth() <= 0)
		{
			cout << "You died!\n";
			// handle player defeat (game over, reset game)
		}
	}
	else if (!isEnemyAdjacentToPlayer())
	{
		cout << "You have evaded the enemy's attack.\n";
	}
}