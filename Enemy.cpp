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
	: type(t)
{
	switch (t)
	{
	case EnemyType::Slime:
		setIcon('s');
		setName("Slime");
		type = EnemyType::Slime;
		setHealth(3);
		setStrength(1);
		setDefense(0);
		break;

	case EnemyType::Leopard:
		setIcon('l');
		setName("Leopard");
		type = EnemyType::Leopard;
		setHealth(19);
		setStrength(3);
		setDefense(1);
		break;

	case EnemyType::Doe:
		setIcon('d');
		setName("Doe");
		type = EnemyType::Doe;
		setHealth(2);
		setStrength(0);
		setDefense(0);
		setMinDamage(0);
		break;
	}
} // end Enemy constructors	


EnemyType Enemy::getType() const
{
	return type;
}

void Enemy::setStunnedState(bool state)
{
	stunned = state;
}

bool Enemy::getStunnedState() const
{
	return stunned;
}
