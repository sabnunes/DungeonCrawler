// Item class declaration

#pragma once
#include <string>
#include "Position2D.h"

enum class ItemType
{
	HealthPotion,
	StrengthPotion,
	DefensePotion
};

// Item class definition
class Item
{
public:
	Item(); // default constructor


	ItemType getType() const; // get items' type
	Position2D getPosition() const; // get item's position
	std::string getName() const; // get item's name
	char getIcon() const; // get item's icon
	bool isCollected() const; // returns if item is collected

	void setType(ItemType newType); // set item's type
	void setPosition(int x, int y); // set item's position
	void collect(); // collect item

private:
	// item attributes for position and representation on the map
	int positionX = 1; // item's x-coordinate position (starting at 1 to avoid wall)
	int positionY = 1; // item's y-coordinate position (starting at 1 to avoid wall)

	ItemType type = ItemType::HealthPotion;
	bool collected = false; // boolean that represents if item is collected
};

