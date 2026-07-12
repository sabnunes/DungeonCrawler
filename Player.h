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
	const std::vector<Item>& getInventory() const;
	const Item& getInventoryItem() const;
	int getInventorySize() const;

	void addInventoryItem(const Item &item);
	void useInventoryItem();

private:
	std::vector<Item> inventory; // inventory storage

};

