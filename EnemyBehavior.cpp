// Member function definitions for EnemyBehavior class

#include "EnemyBehavior.h"

// Default constructor
EnemyBehavior::EnemyBehavior()
	: m_engine(std::random_device{}()) // Initialize the standard Mersenne Twister engine with the seed
{
}

EnemyTurnResult EnemyBehavior::takeTurn(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem)
{
	EnemyTurnResult result = { 0, 0, 0, 0, Position2D { 0, 0 } };
	
	if (world.isEnemyAdjacentToPlayer(enemy))
	{
		CombatResult attackResult = attack(enemy, world, combatSystem);

		result = { 1, attackResult.damage, attackResult.killed };
	}
	else
	{
		MoveResult moveResult = move(enemy, world);

		result = { 0, 0, 0, moveResult.moved, moveResult.deltaPos };
	}

	return result;
}

MoveResult EnemyBehavior::move(Enemy& enemy, GameWorld& world)
{
	MoveResult moveResult = { 0, 0, 0 };

	// STUNED/IDLE LOGIC
	if (enemy.getStunnedState() == true)
	{
		enemy.setStunnedState(false);
		return moveResult;
	}

	// FIND NEXT POS
	int x = 0;
	int y = 0;

	std::vector<Position2D> possibleMoves =
	{
		{ 1,  0 },  // right
		{-1,  0 },  // left
		{ 0,  1 },  // down
		{ 0, -1 },  // up
		{ 1,  1 },  // down-right
		{ 1, -1 },  // up-right
		{-1,  1 },  // down-left
		{-1, -1 }   // up-left
	};

	switch (enemy.getType())
	{
	case EnemyType::Slime:		// Moves randomly
	{
		std::uniform_int_distribution<int> range(-1, 1);

		do
		{
			x = range(m_engine);
			y = range(m_engine);
		} while (x == 0 && y == 0);

		break;
	}
	case EnemyType::Leopard:	// Moves towards player, incl. diagonals
		x = world.getPlayer().getPosition().x > enemy.getPosition().x ? 1 : -1;
		y = world.getPlayer().getPosition().y > enemy.getPosition().y ? 1 : -1;
		break;
	case EnemyType::Doe:		// Moves away from player
	{
		x = world.getPlayer().getPosition().x < enemy.getPosition().x ? 1 : -1;
		y = world.getPlayer().getPosition().y < enemy.getPosition().y ? 1 : -1;
		break;
	}
	default:
		break;
	}

	// VAR TO HOLD POS AND NEXT POS
	Position2D pos = enemy.getPosition();
	Position2D nextPos = { pos.x + x, pos.y + y };

	// PROVIDE 2 ADDTL ALT POS
	if (world.isOccupiedByEntity(nextPos))
	{
		Position2D xOnly = { pos.x + x, pos.y };

		if (!world.isOccupiedByEntity(xOnly))
		{
			nextPos = xOnly;
		}
		else
		{
			Position2D yOnly = { pos.x, pos.y + y };

			if (!world.isOccupiedByEntity(yOnly))
			{
				nextPos = yOnly;
			}
		}
	}

	// VALIDATE & MOVE TO NEXT POS
	if (!world.isOccupiedByEntity(nextPos))
	{
		enemy.setPosition(nextPos);
		moveResult = { 1, Position2D { x, y } };
	}

	return moveResult;
}

CombatResult EnemyBehavior::attack(Enemy& enemy, GameWorld& world, CombatSystem& combatSystem)
{
	return combatSystem.attack(enemy, world.getPlayer());
}