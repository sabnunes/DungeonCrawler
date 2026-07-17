// Member function definitions for EnemyBehavior class

#include "EnemyBehavior.h"
#include "Direction.h"

namespace
{
	constexpr int sign(int value)
	{
		return (value > 0) - (value < 0);
	}
}

EnemyBehavior::EnemyBehavior(Random& random)
	: m_random(random) // Initialize the standard Mersenne Twister engine
{
}

EnemyTurnResult EnemyBehavior::takeTurn(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem)
{
	EnemyTurnResult enemyTurnResult;
	EnemyMoveResult moveResult;
	
	if (world.isEnemyAdjacentToPlayer(enemy))
	{
		CombatResult attackResult = attack(enemy, world, combatSystem);
		enemyTurnResult = { true, attackResult.damage, attackResult.killed, moveResult };
	}
	else
	{
		moveResult = move(enemy, world);
		enemyTurnResult.moveResult = moveResult;
	}

	return enemyTurnResult;
}

EnemyMoveResult EnemyBehavior::move(Enemy& enemy, GameWorld& world)
{
	EnemyMoveResult enemyMoveResult;

	// STUNED/IDLE LOGIC
	if (enemy.getStunnedState())
	{
		enemy.setStunnedState(false);
		enemyMoveResult.wasStunned = true;
		return enemyMoveResult;
	}

	// VAR TO HOLD POS
	Position2D posEnemy = enemy.getPosition();
	Position2D posPlayer = world.getPlayer().getPosition();
	Position2D nextPos = Position2D{ 0, 0 };
	Position2D movement = Position2D{ 0, 0 };
	
	switch (enemy.getType())
	{
	case EnemyType::Slime:		// Moves randomly
	{
		const Direction& direction = directions[m_random.nextInt(0, (int) directions.size() - 1)];
		movement = direction.delta;
		break;
	}
	case EnemyType::Leopard:	// Moves towards player, incl. diagonals
		movement = Position2D{ sign(posPlayer.x - posEnemy.x), sign(posPlayer.y - posEnemy.y) };
		break;
	case EnemyType::Doe:		// Moves away from player
	{
		movement = Position2D{ -sign(posPlayer.x - posEnemy.x), -sign(posPlayer.y - posEnemy.y) };
		break;
	}
	default:
		break;
	}

	nextPos = posEnemy + movement;

	// PROVIDE 2 ALT POS
	if (world.isOccupiedByPlayer(nextPos) || !world.getMap().isWalkable(nextPos) || world.isOccupiedByEnemy(nextPos))
	{
		Position2D xOnlyPos = { posEnemy.x + movement.x, posEnemy.y };

		if (!world.isOccupiedByPlayer(xOnlyPos) && world.getMap().isWalkable(xOnlyPos) && !world.isOccupiedByEnemy(nextPos))
		{
			nextPos = xOnlyPos;
		}
		else
		{
			Position2D yOnlyPos = { posEnemy.x, posEnemy.y + movement.y };

			if (!world.isOccupiedByPlayer(yOnlyPos) && world.getMap().isWalkable(yOnlyPos) && !world.isOccupiedByEnemy(nextPos))
			{
				nextPos = yOnlyPos;
			}
		}
	}

	const Position2D deltaPos = nextPos - posEnemy; // calculating change in position
	
	// VALIDATE & MOVE TO NEXT POS
	if (deltaPos != Position2D{ 0, 0 } && !world.isOccupiedByPlayer(nextPos) && world.getMap().isWalkable(nextPos) && !world.isOccupiedByEnemy(nextPos))
	{
		enemy.setPosition(nextPos);
		enemyMoveResult = { true, deltaPos };
	}

	return enemyMoveResult;
}

CombatResult EnemyBehavior::attack(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem)
{
	return combatSystem.attack(enemy, world.getPlayer());
}