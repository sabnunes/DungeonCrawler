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

	// Inventory management functions
	int getInventorySize() const;
	Item getInventoryItem() const;
	void addInventoryItem(const Item &item);
	void useInventoryItem();
	void printInventory() const;

private:
	std::vector<Item> inventory; // inventory storage

};

