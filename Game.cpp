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
	cout << "Welcome to DUNGEON CRAWLER" << endl;
	cout << "Use WASD keys to move, Q to quit.\n" << endl;

	//cout << "Menu :\n1. Start Game\n2. Quit\nEnter your choice: ";

	running = true; // set running flag to true to start the game loop

	while (running)
	{
		update();
		render();
		input();
	}

	cout << "\nThanks for playing!" << endl;
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

	// Process and verify input for movement and quitting
	switch(input)
	{
		case 'w':
		case 'p':
			// Move player up y--
			cout << "Move up\n";
			move(0, -1);
			break;
		case 'a':
		case 'l':
			// Move player left x--
			cout << "Move left\n";
			move(-1, 0);
			break;
		case 's':
		case ';':
			// Move player down y++
			cout << "Move down\n";
			move(0, 1);
			break;
		case 'd':
		case '\'':
			// Move player right x++
			cout << "Move right\n";
			move(1, 0);
			break;
		case 'q':
		case '[':
			// Quit the game
			running = false;
			break;
		default:
			cout << "Invalid input. Please use WASD keys to move, Q to quit." << endl;
			break;
	}
}

// Update game state based on input and other factors, e.g., move enemies, check for collisions, update health, etc., 
// check for win/loss conditions
void Game::update() const
{
	//cout << "update\n";
}

// Render game state to the screen,	display player health, inventory, etc., display game world, enemies, etc.
void Game::render() const
{
	//printf("\nDUNGEON CRAWLER\n\n"); // top toolbar with game title and stats

	// Render the grid map with the player icon
	//map.print(); // debugging: print the map to the console
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++) {
			if (player.getPosition() == Position2D{ x, y })
			{
				cout << player.getIcon(); // print player icon if player is at this coordinate
			}
			else if (enemy.getPosition() == Position2D{ x, y })
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
	printf("Player Stats | HP: %d | STR: %d | DEF: %d | POS: %d,%d\n\n", 
		player.getHealth(), player.getStrength(), player.getDefense(), player.getPosition().x, player.getPosition().y);
}

// Generate a random valid walkable coordinate and assign it to the player
Position2D Game::generateSpawnPos()
{
	random_device rd; // Obtain a random seed from the hardware
	mt19937 gen(rd()); // Initialize the standard Mersenne Twister engine with the seed
	
	// Define the inclusive range [] for x and y; exclude walls
	uniform_int_distribution<int> rangeX(1, map.getWidth() - 2); 
	uniform_int_distribution<int> rangeY(1, map.getHeight() - 2); 

	Position2D pos; // create a structure to hold the spawn position coordinates

	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
	do
	{
		pos.x = rangeX(gen);
		pos.y = rangeY(gen);
	} while (!map.isWalkable(pos.x, pos.y));

	return pos; // return the generated spawn position coordinates
}

void Game::move(int x, int y)
{
	Position2D pos = player.getPosition();

	// check if the tile above the player is walkable before moving)
	if (map.isWalkable(pos.x + x, pos.y + y)) 
	{
		player.setPosition(pos.x + x, pos.y + y);
	}
	else // if the tile is not walkable, print a message indicating the player cannot move in that direction
	{
		cout << "Cannot move " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ", tile is not walkable.\n";
	}
}