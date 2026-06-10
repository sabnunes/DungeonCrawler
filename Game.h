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
	
		explicit Game(); // default constructor
		void run(); // runs the game

	private:
		bool running; // flag to control game loop

		GridMap map; // the game map
		Player player; // the player character
		Enemy enemy; // the enemy character

		Position2D generateSpawnPos(); // returns a random spawn position

		void input();   // get player input and process it
		void move(int x, int y); // move the player to a new position if it's valid and walkable
		void update() const;  // update game state based on input and other factors
		void render() const;  // render game state to the screen

};