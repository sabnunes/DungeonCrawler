// Game class declaration
#pragma once // prevent multiple inclusions of header 

#include <string>
#include "GridMap.h"
#include "Player.h"
#include "Position2D.h"

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

		Position2D generateSpawnPos(); // returns a random spawn position

		void input() const;   // get player input and process it
		void update() const;  // update game state based on input and other factors
		void render() const;  // render game state to the screen

};