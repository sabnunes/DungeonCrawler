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
	setHealth(15);
	setStrength(1);
	setDefense(0);

} // end Player constructor

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