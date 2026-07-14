// EnemyBehavior class declaration

#pragma once
#include <string>
#include "Enemy.h"
#include "GameWorld.h"
#include "CombatSystem.h"

class Random; // forward declaration since only storing a reference

struct EnemyMoveResult
{
	bool moved = false;
	Position2D deltaPos = Position2D{ 0, 0 };
	bool wasStunned = false;
};

struct EnemyTurnResult
{
	bool attacked = false;
	int damage = 0;
	bool killedPlayer = false;

	EnemyMoveResult moveResult;
};

class EnemyBehavior
{
public:
	explicit EnemyBehavior(Random& random);

	EnemyTurnResult takeTurn(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

private:
	Random& m_random;

	EnemyMoveResult move(Enemy& enemy, GameWorld& world);
	CombatResult attack(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

	//bool isStunned();
};

