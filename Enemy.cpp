// Member-function definitions for the Enemy class
#include <iostream>
#include "Enemy.h"
using namespace std;

// Constructor
Enemy::Enemy()
{

}

// Constructor
Enemy::Enemy(EnemyType t)
{
	switch (t)
	{
	case EnemyType::Slime:
		health = 3;
		strength = 1;
		defense = 0;
		icon = 's';
		name = "Slime";
		type = EnemyType::Slime;
		break;

	case EnemyType::Leopard:
		health = 10;
		strength = 3;
		defense = 1;
		icon = 'l';
		name = "Leopard";
		type = EnemyType::Leopard;
		break;

	case EnemyType::Doe:
		health = 2;
		strength = 0;
		defense = 0;
		icon = 'd';
		name = "Doe";
		type = EnemyType::Doe;
		break;
	}
} // end Enemy constructors	


EnemyType Enemy::getType() const
{
	return type;
}

std::string Enemy::getName() const
{
	return name;
}

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

// Get enemy char icon
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

void Enemy::setStunnedState(bool state)
{
	isStunned = state;
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

// Check if the enemy is alive (health > 0)
bool Enemy::isAlive() const
{
	return getHealth() > 0;
}

bool Enemy::getStunnedState() const
{
	return isStunned;
}
