// CombatSystem class declaration

#pragma once
#include "Character.h"

// Structure to represent combat result variables
struct CombatResult
{
	int damage;
	bool killed;
};

class CombatSystem
{
public:
	CombatSystem();												// default constructor

	CombatResult attack(const Character& attacker, 
							  Character& defender);				// perform attack from attacker to defender and return damage and if defender is dead
	int calculateDamage(const Character& attacker,
						const Character& defender) const;		// calculate damage dealt by attacker to defender

private:
	void applyDamage(Character& defender, int damage) const;	// applies damage to defender's health
	bool isDead(Character& defender) const;						// returns if defender is dead

};

