// Member-function definitions for the Player class
#include <iostream>
#include "Player.h"

using namespace std;

// Constructor
Player::Player()
{
} // end Player constructor

// Get player's health
int Player::getHealth() const
{
	return health;
}

// Get player's position
Position2D Player::getPosition() const
{
	Position2D pos;
	pos.x = positionX;
	pos.y = positionY;
	return pos;
}

// Get player's char icon
char Player::getIcon() const
{
	return icon;
}

// Set player's position
void Player::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

// Get player's x-coordinate position
void Player::setHealth(int newHealth)
{
	health = newHealth;
	if (health <= 0)
	{
		health = 0; // Ensure health does not go below 0
	}
}

// Set player's strength
void Player::setStrength(int newStrength)
{
	strength = newStrength;
}

// Set player's defense
void Player::setDefense(int newDefense)
{
	defense = newDefense;
}

// Returns player inventory size
int Player::getInventorySize() const
{
	return (int) inventory.size();
}

// Prints player's inventory items
void Player::printInventory() const
{
	if (inventory.size() > 0)
	{
		for (size_t i = 0; i < inventory.size() -1; i++)
		{
			cout << inventory[i].getName() << ", ";
		}

		cout << inventory[inventory.size()-1].getName();
	}
	else
	{
		cout << "none";
	}
}

// Adds item to player inventory
void Player::addInventoryItem(const Item &item)
{
	inventory.push_back(item);
}

// Returns last item in player inventory
Item Player::getInventoryItem() const
{
	return inventory.back();
}

// Removes last item from player's inventory
void Player::useInventoryItem()
{
	inventory.pop_back(); // removes last only
}

// Get player's strength
int Player::getStrength() const
{
	return strength;
}

// Get player's defense
int Player::getDefense() const
{
	return defense;
}

// Check if the player is alive (health > 0)
bool Player::isAlive() const
{
	return getHealth() > 0;
}
