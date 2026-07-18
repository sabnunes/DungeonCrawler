// Member-function definitions for the Item class
#include <iostream>
#include "Item.h"

// Constructor
Item::Item()
{

} // end Item constructor

Item::Item(ItemType t)
	: type(t)
{
	type = t;

	switch (t)
	{
	case ItemType::HealthPotion:
		setName("Health Potion");
		setIcon('H');
		itemValue = 10;
		break;

	case ItemType::StrengthPotion:
		setName("Strength Potion");
		setIcon('S');
		itemValue = 1;
		break;

	case ItemType::DefensePotion:
		setName("Defense Potion");
		setIcon('D');
		itemValue = 1;
		break;
	}
}

ItemType Item::getType() const
{
	return type;
}

bool Item::isCollected() const
{
	return collected;
}

void Item::collect()
{
	collected = true;
}

int Item::getValue() const
{
	return itemValue;
}
