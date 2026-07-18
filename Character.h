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

	int getMinDamage() const;       // returns minimum damage character can do
	void setMinDamage(int damage);  // sets minimum damage character can do

	bool isAlive() const;           // returns if character is alive (health > 0)

    void modifyHealth(int value);   // modifies health parameter by value
    void modifyStrength(int value); // modifies strength parameter by value
    void modifyDefense(int value);  // modifies defense parameter by value

private:
    int health = 10;
    int strength = 1;
    int defense = 0;
	int minDamage = 1;

};
