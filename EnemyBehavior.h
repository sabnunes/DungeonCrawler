// EnemyBehavior class declaration

#pragma once
#include "Enemy.h"
#include "GameWorld.h"
#include "CombatSystem.h"

class Random; // forward declaration since only storing a reference

// Structure that represents enemy move result variables
struct EnemyMoveResult
{
	bool moved = false;
	Position2D deltaPos = Position2D{ 0, 0 };
	bool wasStunned = false;
};

// Structure that represents enemy turn result variables
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
	explicit EnemyBehavior(Random& random);					// parameterized constructor

	EnemyTurnResult takeTurn(Enemy& enemy, GameWorld& world, 
		CombatSystem& combatSystem);						// processes enemy turn and returns enemy turn result

private:
	Random& m_random;										// reference to random created in game class

	CombatResult attack(Enemy& enemy, GameWorld& world, 
		CombatSystem& combatSystem);						// processes enemy attack and returns combat result
	EnemyMoveResult move(Enemy& enemy, GameWorld& world);	// processes enemy move and resturns enemy move result

	//bool isStunned(); // returns if enemy is stunned
};

