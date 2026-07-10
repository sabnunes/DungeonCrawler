// Item class declaration

#pragma once
#include "Entity.h"

enum class ItemType
{
	HealthPotion,
	StrengthPotion,
	DefensePotion,

	count // used to get the number of item types
};

// Item class definition
class Item : public Entity
{
public:
	Item();						// default constructor
	explicit Item(ItemType t);	// constructor with item type

	ItemType getType() const;		// get item type
	void setType(ItemType newType); // set item type

	bool isCollected() const;	// returns if item is collected
	void collect();				// collect item

	int getValue() const;

private:
	ItemType type = ItemType::HealthPotion;

	bool collected = false; // boolean that represents if item is collected

	int itemValue = 1;
};

