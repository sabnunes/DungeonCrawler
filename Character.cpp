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

	if (health < 0)
	{
		health = 0;
	}
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

int Character::getMinDamage() const
{
	return minDamage;
}

void Character::setMinDamage(int d)
{
	minDamage = d;
}

bool Character::isAlive() const
{
	return getHealth() > 0;
}

void Character::modifyHealth(int v)
{
	setHealth(getHealth() + v);
}

void Character::modifyStrength(int v)
{
	setStrength(getStrength() + v);
}

void Character::modifyDefense(int v)
{
	setDefense(getDefense() + v);
}
