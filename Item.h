// Item class declaration

#pragma once
#include "Entity.h"

// item types that exist in game
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
	Item();	
	explicit Item(ItemType t);	// constructor with item type

	ItemType getType() const;	// get item type

	bool isCollected() const;	// returns if item is collected
	void collect();				// collect item

	int getValue() const;		// gets upgrade value of item

private:
	ItemType type = ItemType::HealthPotion;

	bool collected = false;		// returns if item is collected

	int itemValue = 1;			// default item upgrade value
};

