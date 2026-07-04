// Member-function definitions for the Item class
#include <iostream>
#include "Item.h"

// Constructor
Item::Item()
{

} // end Item constructor

ItemType Item::getType() const
{
	return type;
}

// Get item's position
Position2D Item::getPosition() const
{
	Position2D pos;
	pos.x = position.x;
	pos.y = position.y;
	return pos;
}

// Returns if item is collected
bool Item::isCollected() const
{
	return collected;
}

void Item::setType(ItemType newType)
{
	type = newType;
}

// Set item's position
void Item::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

// Sets collected item to true
void Item::collect()
{
	collected = true;
}


// Get the character representation of the item
char Item::getIcon() const
{
	switch (type)
	{
	case ItemType::HealthPotion:
		return 'H'; 
	case ItemType::StrengthPotion:
		return 'S'; 
	case ItemType::DefensePotion:
		return 'D'; 
	default:
		return '?'; 
	}
}

std::string Item::getName() const
{
	switch (type)
	{
	case ItemType::HealthPotion:
		return "Health Potion";
	case ItemType::StrengthPotion:
		return "Strength Potion";
	case ItemType::DefensePotion:
		return "Defense Potion";
	default:
		return "Error: unknown item type name";
	}
}
