// Member-function definitions for the Item class
#include <iostream>
#include "Item.h"

// Constructor
Item::Item()
{

} // end Item constructor

// Get item's position
Position2D Item::getPosition() const
{
	Position2D pos;
	pos.x = positionX;
	pos.y = positionY;
	return pos;
}

// Get item's char icon
char Item::getIcon() const
{
	return icon;
}

// Get item's name
std::string Item::getName() const
{
	return name;
}

// Returns if item is collected
bool Item::isCollected() const
{
	return collected;
}

// Set item's position
void Item::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

// Sets collected item to true
void Item::collect()
{
	collected = true;
}




//// Get the item type at a specific position
//ItemType Item::getItem(int x, int y) const
//{
//	return ItemType::HealthPotion;
//}
//
//// Get the character representation of the item at a specific position
//char Item::getItemIcon(string name) const
//{
//	switch (1)
//	{
//	case Item::HealthPotion:
//		return 'X'; 
//	case Item::Floor:
//		return ' '; 
//	default:
//		return '?'; 
//	}
//}
