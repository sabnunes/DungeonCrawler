// Member-function definitions for the CombatSystem class

#include <algorithm>
#include "CombatSystem.h"

CombatSystem::CombatSystem()
{

} // end default constructor

bool CombatSystem::attack(const Character& attacker, Character& defender)
{
	applyDamage(defender, calculateDamage(attacker, defender));

	return isDead(defender);
}

int CombatSystem::calculateDamage(const Character& attacker, const Character& defender) const
{
	return std::max(attacker.getMinDamage(), attacker.getStrength() - attacker.getDefense());
}

void CombatSystem::applyDamage(Character& defender, int damage) const
{
	defender.setHealth(defender.getHealth() - damage);
}

bool CombatSystem::isDead(Character& defender) const
{
	return !defender.isAlive();
}


