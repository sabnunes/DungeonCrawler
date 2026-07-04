// CombatSystem class declaration

#pragma once

/*
Combat rules are currently duplicated.
You can unit test combat without running the whole game.
It shows separation of rules from presentation.

Conceptually, CombatSystem should answer questions like :
How much damage does attacker deal ?
Did the defender die ?
What stat changes happen after defeat ?

But it should not print UI text.That should remain outside or be returned as events / messages.

combat system: A cleaner design:
calculateDamage(attackerStats, defenderStats)
applyDamage(entity, damage)
resolveDeath(entity)
the rules should live in one place.
*/


class CombatSystem
{
public:
	CombatSystem(); // default constructor

	//bool attack(Character& attacker, 
				//Character& defender); // perform an attack from attacker to defender and return if defender is dead

private:
	//int calculateDamage(const Character& attacker,
						//const Character& defender) const; // calculate damage dealt by attacker to defender
	//void applyDamage(Character& defenderint damage) const; // apply damage to defender's health
	//bool isDead(Character& defender) const; // check if defender is dead and handle death

};

