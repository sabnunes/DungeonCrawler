// Character class declaration

#pragma once
#include "Entity.h"

class Character : public Entity
{
public:
	Character(); // default constructor

	// Get and set character attributes (health, strength, defense)
    int getHealth() const;
    void setHealth(int health);

    int getStrength() const;
    void setStrength(int strength);

    int getDefense() const;
    void setDefense(int defense);

	bool isAlive() const; // Returns if character is alive (health > 0)

private:
    int health = 10;
    int strength = 1;
    int defense = 0;

};
