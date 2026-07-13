// Enemy class declaration
#pragma once
#include "Character.h"

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
	Enemy(); // default constructor
	explicit Enemy(EnemyType t); // constructor with enemy type

	EnemyType getType() const;		// returns enemy type

	bool getStunnedState() const;		// returns if enemy is stunned
	void setStunnedState(bool state);	// set enemy stunned state

private:
	// enemy representation on the map
	EnemyType type = EnemyType::Slime;		// enemy type

	bool stunned = true;

};