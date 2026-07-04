// Player class declaration
#pragma once
#include <vector>
#include "Character.h"
#include "Item.h"

// class Player definition
class Player : public Character
{
public:
	Player(); // default constructor

	char getIcon() const; // Get player's char icon

	// Inventory management functions
	int getInventorySize() const;
	void addInventoryItem(const Item &item);
	Item getInventoryItem() const;
	void useInventoryItem();
	void printInventory() const;

private:
	const char icon = 'P';	// representation on the map
		
	std::vector<Item> inventory; // inventory storage
};

