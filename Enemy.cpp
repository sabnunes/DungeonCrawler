// Member-function definitions for the Enemy class
#include <iostream>
#include "Enemy.h"

// Constructor
Enemy::Enemy()
{
} // end Enemy constructor	

// Get enemy's health
int Enemy::getHealth() const
{
	return health;
}

// Get enemy's position
Position2D Enemy::getPosition() const
{
	Position2D pos;
	pos.x = positionX;
	pos.y = positionY;
	return pos;
}

// Get enemy's char icon
char Enemy::getIcon() const
{
	return icon;
}

// Set enemy's position
void Enemy::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

// Get enemy's x-coordinate position
void Enemy::setHealth(int newHealth)
{
	health = newHealth;
	if (health <= 0)
	{
		health = 0; // Ensure health does not go below 0
	}
}

// Get enemy's strength
int Enemy::getStrength() const
{
	return strength;
}

// Get enemy's defense
int Enemy::getDefense() const
{
	return defense;
}