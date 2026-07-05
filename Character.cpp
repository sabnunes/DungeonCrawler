// Member-function definitions for the Character class

#include "Character.h"

Character::Character()
{

} // end of default constructor

int Character::getHealth() const
{
	return health;
}

void Character::setHealth(int h)
{
	health = h;
}

int Character::getStrength() const
{
	return strength;
}

void Character::setStrength(int s)
{
	strength = s;
}

int Character::getDefense() const
{
	return defense;
}

void Character::setDefense(int d)
{
	defense = d;
}

bool Character::isAlive() const
{
	return getHealth() > 0;
}