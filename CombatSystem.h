// CombatSystem class declaration

#pragma once
#include "Character.h"

struct CombatResult
{
	int damage;
	bool killed;
};

class CombatSystem
{
public:
	CombatSystem(); // default constructor

	CombatResult attack(const Character& attacker, 
				Character& defender); // perform an attack from attacker to defender and return if defender is dead
	int calculateDamage(const Character& attacker,
						const Character& defender) const; // calculate damage dealt by attacker to defender

private:
	void applyDamage(Character& defender, int damage) const; // apply damage to defender's health
	bool isDead(Character& defender) const; // check if defender is dead and handle death

	void playerAttack();	// process player attacking the enemy


};

