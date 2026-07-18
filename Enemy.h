// Enemy class declaration
#pragma once
#include "Character.h"

// enemy types that exist in game
enum class EnemyType
{
	Slime,
	Leopard,
	Doe
};

// class Enemy definition
class Enemy : public Character
{
public:
	Enemy();
	explicit Enemy(EnemyType t);		// constructor with enemy type

	EnemyType getType() const;			// returns enemy type

	bool getStunnedState() const;		// returns if enemy is stunned
	void setStunnedState(bool state);	// set enemy stunned state

private:
	EnemyType type = EnemyType::Slime;	// enemy type

	bool stunned = true;

};