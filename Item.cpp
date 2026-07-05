// Member-function definitions for the Item class
#include <iostream>
#include "Item.h"

// Constructor
Item::Item()
{

} // end Item constructor

Item::Item(ItemType t)
{
	type = t;

	switch (t)
	{
	case ItemType::HealthPotion:
		setName("Health Potion");
		setIcon('H');
		break;

	case ItemType::StrengthPotion:
		setName("Strength Potion");
		setIcon('S');
		break;

	case ItemType::DefensePotion:
		setName("Defense Potion");
		setIcon('D');
		break;
	}
}

ItemType Item::getType() const
{
	return type;
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

// Sets collected item to true
void Item::collect()
{
	collected = true;
}
