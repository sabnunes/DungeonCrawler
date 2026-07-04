// Enemy class declaration
#pragma once
#include <string>
#include "Position2D.h"

enum class EnemyType
{
	Slime,
	Leopard,
	Doe
};

// class Enemy definition
class Enemy
{
public:
	Enemy(); // default constructor
	explicit Enemy(EnemyType t); // constructor with enemy type

	// set functions for enemy attributes (e.g., health, position)
	EnemyType getType() const;		// returns enemy type
	Position2D getPosition() const; // returns enemy position
	std::string getName() const;	// returns enemy name
	char getIcon() const;			// returns enemy icon
	int getHealth() const;			// returns enemy health
	int getStrength() const;		// returns enemy strength
	int getDefense() const;			// returns enemy defense
	bool isAlive() const;			// returns if enemy is alive or dead
	bool getStunnedState() const;	// returns if enemy is stunned

	// get functions for enemy attributes (e.g., health, position)
	void setPosition(int x, int y);		// set enemy position
	void setHealth(int newHealth);		// set enemy health
	void setStunnedState(bool state);	// set enemy stunned state

private:
	// enemy attributes for position and representation on the map
	Position2D position = Position2D{ 1, 1 };	// position on the map
	EnemyType type = EnemyType::Slime;			// enemy type

	char icon = 'E';			// representation on the map
	std::string name = "Enemy";	// name

	// enemy attributes for combat and other mechanics
	int health = 1;		// enemy health
	int strength = 0;	// enemy strength
	int defense = 0;	// enemy defense

	bool isStunned = true;
};