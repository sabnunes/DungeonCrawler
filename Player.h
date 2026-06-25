// Player class declaration
#pragma once
#include <vector>
#include "Position2D.h"
#include "Item.h"

// class Player definition
class Player
{
public:
	explicit Player(); // default constructor

	// get functions for player attributes (e.g., health, position)
	Position2D getPosition() const; // get player's position
	char getIcon() const; // get player's icon
	int getHealth() const; // get player's health
	int getStrength() const; // get player's strength
	int getDefense() const; // get player's defense
	bool isAlive() const; // check if the player is alive or defeated

	// set functions for player attributes (e.g., health, position)
	void setPosition(int x, int y); // set player's position
	void setHealth(int newHealth); // set player's health
	void setStrength(int newStrength); // set player's strength
	void setDefense(int newDefense); // set player's defense

	int getInventorySize() const;
	void addInventoryItem(const Item &item);
	Item getInventoryItem() const;
	void useInventoryItem();
	void printInventory() const;

private:
	// player attributes for position and representation on the map
	int positionX = 1; // player's x-coordinate position (starting at 1 to avoid wall)
	int positionY =	1; // player's y-coordinate position (starting at 1 to avoid wall)

	const char icon = 'P'; // representation of the player on the map

	// player attributes for combat and other mechanics
	int health = 15; // player's health
	int strength = 1; // player's strength (for combat calculations)
	int defense = 0; // player's defense (for combat calculations)
	
	std::vector<Item> inventory; // loot storage
};

