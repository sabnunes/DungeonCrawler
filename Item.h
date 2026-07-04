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
	Position2D position = Position2D{ 1, 1 };	// position on the map

	ItemType type = ItemType::HealthPotion;
	bool collected = false; // boolean that represents if item is collected
};

