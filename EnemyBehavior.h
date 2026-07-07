// EnemyBehavior class declaration

#pragma once
#include "Enemy.h"
#include "Player.h"
#include "GameWorld.h"

class EnemyBehavior
{
public:
	EnemyBehavior();

	void takeTurn(Enemy& enemy, const Player& player, const GameWorld& world);

private:
	void moveEnemy(Enemy& enemy, const GameWorld& world);

	void attackPlayer(Enemy& enemy);

};

