// Enemy class declaration
#pragma once
#include "Position2D.h"

// class Enemy definition
class Enemy
{
public:
	explicit Enemy(); // default constructor

	// set functions for enemy attributes (e.g., health, position)
	Position2D getPosition() const; // get enemy's x-coordinate position
	char getIcon() const; // get enemy's icon
	int getHealth() const; // get enemy's health
	int getStrength() const; // get enemy's strength
	int getDefense() const; // get enemy's defense

	// get functions for enemy attributes (e.g., health, position)
	void setPosition(int x, int y); // set enemy's x-coordinate position
	void setHealth(int newHealth); // set enemy's health


private:
	// enemy attributes for position and representation on the map
	int positionX = 1; // enemy's x-coordinate position (starting at 1 to avoid wall)
	int positionY = 1; // enemy's y-coordinate position (starting at 1 to avoid wall)

	char icon = 'E'; // representation of the enemy on the map

	// enemy attributes for combat and other mechanics
	int health = 100; // enemy's health
	int strength = 1; // enemy's strength (for combat calculations)
	int defense = 0; // enemy's defense (for combat calculations)

};