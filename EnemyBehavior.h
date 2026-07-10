// EnemyBehavior class declaration

#pragma once
#include <random>
#include "Enemy.h"
#include "GameWorld.h"
#include "CombatSystem.h"

struct EnemyTurnResult
{
	bool attacked;
	int damage;
	bool killedPlayer;

	bool moved;
	Position2D deltaPos;
};

struct MoveResult
{
	bool moved;
	Position2D deltaPos;
};

class EnemyBehavior
{
public:
	EnemyBehavior();

	EnemyTurnResult takeTurn(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

private:
	std::mt19937 m_engine;	// Obtain a random seed from the hardware

	MoveResult move(Enemy& enemy, GameWorld& world);
	CombatResult attack(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem);

	//void chooseDirection();
	//void findNextPosition();
	//void findAlternativePosition();
	//bool isStunned();
};

