// Member-function definitions for the Player class
#include <iostream>
#include "Player.h"

using namespace std;

// Constructor
Player::Player()
{
	// player attributes
	setIcon('P');
	setName("Player");
	setHealth(10);
	setStrength(1);
	setDefense(0);

} // end Player constructor

const std::vector<Item>& Player::getInventory() const
{
	return inventory;
}

// Returns player inventory size
int Player::getInventorySize() const
{
	return (int) inventory.size();
}

// Adds item to player inventory
void Player::addInventoryItem(const Item &item)
{
	inventory.push_back(item);
}

// Returns last item in player inventory
const Item& Player::getInventoryItem() const
{
	return inventory.back();
}

// Removes last item from player's inventory
void Player::useInventoryItem()
{
	inventory.pop_back(); // removes last only
}