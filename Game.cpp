// Member function definitions for Game class
#include <iostream>
#include <random>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
{
	map.initialize();// initialize the map

	Position2D spawnPos; // create a structure to hold the spawn position coordinates
	spawnPos = generateSpawnPos(); // generate a random spawn position for the player

	// Set the player's position to the generated spawn position
	player.setPosition(spawnPos.x, spawnPos.y);

} // end Game constructor

// run the game: welcome message, process main game loop (input, update, render)
void Game::run()
{
	cout << "Welcome to DUNGEON CRAWLER" << endl;
	printf("Use WASD keys to move, Q to quit.\n\n");

	running = true; // set running flag to true to start the game loop

	while (running)
	{
		input();
		update();
		render();
	}
} // end function run

// Get player input and process it, e.g., move player position, update health, etc
void Game::input() const
{
	string input;
	cout << "Enter input: ";
	cin >> input;
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
	printf("\nDUNGEON CRAWLER\n\n");

	// Render the grid map with the player icon
	//map.print(); // debugging: print the map to the console
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++) {
			if (player.getPosition() == Position2D{ x, y })
			{
				cout << player.getIcon(); // print player icon if player is at this coordinate
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
