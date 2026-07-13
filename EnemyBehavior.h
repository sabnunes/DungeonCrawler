// EnemyBehavior class declaration

#pragma once
#include <random>
#include <string>
#include "Enemy.h"
#include "GameWorld.h"
#include "CombatSystem.h"

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
	EnemyBehavior();

	EnemyTurnResult takeTurn(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

private:
	std::mt19937 m_engine;	// Obtain a random seed from the hardware
	
	EnemyMoveResult move(Enemy& enemy, GameWorld& world);
	CombatResult attack(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

	//bool isStunned();
};

