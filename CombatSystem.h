// CombatSystem class declaration

#pragma once
#include "Character.h"

/*
Combat rules are currently duplicated.
You can unit test combat without running the whole game.
It shows separation of rules from presentation.

Conceptually, CombatSystem should answer questions like :
How much damage does attacker deal ?
Did the defender die ?
What stat changes happen after defeat ?

But it should not print UI text.That should remain outside or be returned as events / messages
*/


class CombatSystem
{
public:
	CombatSystem(); // default constructor

	bool attack(Character& attacker, 
				Character& defender); // perform an attack from attacker to defender and return if defender is dead
	int calculateDamage(const Character& attacker,
						const Character& defender) const; // calculate damage dealt by attacker to defender

private:
	void applyDamage(Character& defender, int damage) const; // apply damage to defender's health
	bool isDead(Character& defender) const; // check if defender is dead and handle death

};

