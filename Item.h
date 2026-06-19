// Item class declaration

#pragma once
#include <string>
#include "Position2D.h"

enum class ItemType
{
	HealthPotion,
	StrengthPotion,
	Sword,
	Shield
};

// Item class definition
class Item
{
public:
	explicit Item(); // default constructor

	Position2D getPosition() const; // get item's position
	char getIcon() const; // get item's icon
	std::string getName() const; // get item's name
	bool isCollected() const; // returns if item is collected

	void setPosition(int x, int y); // set item's position
	void collect(); // collect item

private:
	// item attributes for position and representation on the map
	int positionX = 1; // item's x-coordinate position (starting at 1 to avoid wall)
	int positionY = 1; // item's y-coordinate position (starting at 1 to avoid wall)

	const char icon = 'I'; // representation of the item on the map
	const std::string name = "Health Potion"; // item name
    bool collected = false; // boolean that represents if item is collected


};

