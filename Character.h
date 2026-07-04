// Character class declaration

#pragma once
#include "Position2D.h"

class Character
{
public:
	Character(); // default constructor

	// Get and set character attributes (health, strength, defense, position, icon)
    int getHealth() const;
    void setHealth(int health);

    int getStrength() const;
    void setStrength(int strength);

    int getDefense() const;
    void setDefense(int defense);

    Position2D getPosition() const;
    void setPosition(Position2D newPosition);

	bool isAlive() const; // Returns if character is alive (health > 0)

protected:
    int health = 10;
    int strength = 1;
    int defense = 0;
    Position2D position = Position2D{ 1, 1 };
};
