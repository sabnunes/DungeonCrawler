// Member function definitions for EnemyBehavior class

#include "EnemyBehavior.h"

EnemyBehavior::EnemyBehavior()
{
}

void EnemyBehavior::takeTurn(Enemy& enemy, const Player& player, const GameWorld& world)
{
	//if (isLiveEnemyAdjacentToPlayer(enemy))
	{
		moveEnemy(enemy, world);

	}
	//else
	{
		attackPlayer(enemy);

	}
}

void EnemyBehavior::moveEnemy(Enemy& enemy, const GameWorld& world)
{

}

void EnemyBehavior::attackPlayer(Enemy& enemy)
{
}