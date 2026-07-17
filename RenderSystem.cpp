// Member function definitions for RenderSystem class

#include <iostream>
#include <iomanip>
#include "RenderSystem.h"
#include "Direction.h"

using namespace std;

// Default constructor
RenderSystem::RenderSystem()
{

}

void RenderSystem::render(const GameWorld& world, bool playerTurn) const
{
	renderStats(world);
	renderMap(world);

	renderStatusMessages(world, playerTurn);
}

void RenderSystem::printHeader() const
{
	cout << "=================================\n      DUNGEON CRAWLER v1.0		\n=================================\n" << endl;
}

void RenderSystem::printLegend() const
{
	cout << "LEGEND\n---------------------------------\n";
	cout << left;

	auto col = [](const string& text)
		{
			cout << setw(12) << text;
		};

	col("CONTROLS");	col("ENEMIES");		col("TERRAIN");	cout << "\n";
	col("W north");		col("s Slime");		col("^ tree");		cout << "\n";
	col("A west");		col("l Leopard");	col(", grass");		cout << "\n";
	col("S south");		col("d Doe");		col("~ water");		cout << "\n";
	col("D east");		col("");			col("* rock");      cout << "\n";
	col("X attack");	col("LOOT");		col("");			cout << "\n";
	col("E equip");		col("H HP+10");		col("");			cout << "\n";
	col("U use loot");	col("S STR++");		col("HERO");		cout << "\n";
	col("Q quit");		col("D DEF++");		col("P Player");	cout << "\n";

	cout << "---------------------------------" << endl;
}

void RenderSystem::printSeed(unsigned seed) const
{
	cout << "GAME SEED " << seed << endl << endl;
}

void RenderSystem::printLevel(const LevelDescription& level) const
{
	cout << "\n---------------------------------\n LEVEL "
		<< level.getNumber()
		<< " "
		<< level.getName()
		<< "\n---------------------------------"
		<< endl << endl;
}

void RenderSystem::printNextLevel() const
{
	cout << "\nYou've defeated all enemies! NEXT LEVEL!\n" << endl;
}

void RenderSystem::printInvalidInput() const
{
	cout << "Invalid input. Use WASD keys to move, Q to quit.\n" << endl;
}

void RenderSystem::printPlayerMove(const GameWorld& world, const PlayerMoveResult& moveResult) const
{
	Position2D pos = world.getPlayer().getPosition();

	// check if the tile is walkable before moving and not occupied by the enemy
	if (moveResult.moved)
	{
		cout << "You moved "
			<< directionName(moveResult.deltaPos)
			<< "." << endl;

		for (const Item& item : world.getItems())
		{
			if (pos == item.getPosition() && !item.isCollected())
			{
				cout << "You found a " << item.getName() << "! Pick it up on your next turn." << endl;
			}
		}
	}
	else if (moveResult.occupiedByEnemy)
	{
		cout << "You cannot move there! An enemy lies in your path." << endl;
	}
	else
	{
		cout << "You cannot move there!" << endl;
	}
}

void RenderSystem::printPlayerAttack(const Enemy* enemy, const CombatResult& result, const bool successfulAttack) const
{
	cout << "You attempt an attack on the enemy." << endl;
	
	if (successfulAttack)
	{
		string enemyName = enemy->getName();

		cout << "You slash the " << enemyName << "! ";

		if (result.killed)
		{
			cout << enemyName << " is dead! Strength increased +1." << endl;
		}
		else
		{
			cout << result.damage << " damage dealt." << endl;
			cout << enemyName << " preparing counterattack." << endl;
		}
	}

	if (!successfulAttack)
	{
		cout << "No enemy in range." << endl;
	}
}

void RenderSystem::printPlayerCollectItem(const PlayerCollectedItem& itemCollected) const
{
	if (itemCollected.collected)
	{
		cout << itemCollected.item->getName() << " added to inventory!";
	}
	else
	{
		if (itemCollected.noItemHereButItemExists)
		{
			cout << "To pick up an item, you must travel to its location.";
		}
		else
		{
			cout << "No items exist.";
		}
	}

	cout << endl;
}

void RenderSystem::printPlayerUseItem(const Item* item) const
{
	if (item == nullptr)
	{
		cout << "You do not have any loot." << endl;
		return;
	}

	const int itemValue = item->getValue();
	const string& itemName = item->getName();
	
	switch (item->getType())
	{
	case ItemType::HealthPotion: // give player +HP
		cout << "You've gained +" << itemValue << " HP by consuming the " << itemName << "!" << endl;
		break;
	case ItemType::StrengthPotion: // give player +STR
		cout << "You've gained +" << itemValue << " strength by consuming the " << itemName << "!" << endl;
		break;
	case ItemType::DefensePotion: // give player +1 DEF
		cout << "You've gained +" << itemValue << " defense by consuming the " << itemName << "!" << endl;
		break;
	default:
		cout << "Unknown loot." << endl;
		break;
	}
}

void RenderSystem::printEnemyTurn(const Enemy& enemy, const EnemyTurnResult& enemyTurnResult) const
{
	if (enemyTurnResult.attacked)
	{
		cout << enemy.getName() << " attacked you!" << endl;

		if (enemyTurnResult.damage > 0)
		{
			cout << enemy.getName() << " attack successful. You lost " << enemyTurnResult.damage << " HP." << endl;

			if (enemyTurnResult.killedPlayer)
			{
				cout << "You died!" << endl;
			}
		}
		else
		{
			cout << enemy.getName() << " attack unsuccessful." << endl;
		}
	}
	else
	{
		if (enemyTurnResult.moveResult.wasStunned)
		{
			cout << enemy.getName() << " gathering its senses." << endl;
			return;
		}
		
		if (enemyTurnResult.moveResult.moved)
		{
			Position2D deltaMove = enemyTurnResult.moveResult.deltaPos;

			cout << enemy.getName() << " moved "
				<< directionName(deltaMove)
				<< "." << endl;
		}
		else
		{
			cout << enemy.getName() << " attempted move, but cannot move there!" << endl;
		}
	}
}

void RenderSystem::printGameEnd(const bool won) const
{
	cout << (won ? "You've defeated all enemies! You win!" : "You are dead. Game over.") << endl;
}

void RenderSystem::printGoodbye() const
{
	cout << "Thanks for playing!" << endl;
}

void RenderSystem::renderStats(const GameWorld& world) const
{
	// Print player and enemy stats
	cout << left << setw(8) << "Player"
		<< right << setw(3) << world.getPlayer().getHealth() << " HP  "
		<< setw(2) << world.getPlayer().getStrength() << " STR  "
		<< setw(2) << world.getPlayer().getDefense() << " DEF";
	
	renderPlayerInventory(world);

	for (const Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			cout << left << setw(8) << enemy.getName()
				<< right << setw(3) << enemy.getHealth() << " HP  "
				<< setw(2) << enemy.getStrength() << " STR  "
				<< setw(2) << enemy.getDefense() << " DEF\n";
		}
	}
	cout << endl; // empty line

}

void RenderSystem::renderPlayerInventory(const GameWorld& world) const
{
	if (world.getPlayer().getInventorySize() > 0)
	{
		cout << "  LOOT ";
		const vector<Item>& inventory = world.getPlayer().getInventory();

		for (size_t i = 0; i < inventory.size() - 1; i++)
		{
			cout << inventory[i].getName() << ", ";
		}

		cout << inventory[inventory.size() - 1].getName();
	}
	cout << endl;
}

void RenderSystem::renderMap(const GameWorld& world) const
{
	// Render the grid map with the player icon
	for (int y = 0; y < world.getMap().getHeight(); y++)
	{
		for (int x = 0; x < world.getMap().getWidth(); x++)
		{
			Position2D pos = Position2D{ x, y };

			// PLAYER
			if (world.getPlayer().getPosition() == pos && world.getPlayer().isAlive())
			{
				cout << world.getPlayer().getIcon(); // print player icon if player is at this coordinate
			}
			// ENEMY
			else
			{
				bool enemyDrawn = false;

				for (const Enemy& enemy : world.getEnemies())
				{
					if (enemy.isAlive() && enemy.getPosition() == pos)
					{
						cout << enemy.getIcon(); // print enemy icon if enemy is at this coordinate
						enemyDrawn = true;
						break;
					}
				}

				// ITEM SEARCH
				if (!enemyDrawn)
				{
					bool itemDrawn = false;

					for (const Item& item : world.getItems())
					{
						if (!item.isCollected() &&
							item.getPosition() == pos)
						{
							cout << item.getIcon();
							itemDrawn = true;
							break;
						}
					}

					// TILE
					if (!itemDrawn)
					{
						cout << world.getMap().getTileIcon(pos);
					}
				}
			}
		}
		cout << endl; // New line after each row
	}
}

void RenderSystem::renderStatusMessages(const GameWorld& world, const bool playerTurn) const
{
	if (world.getPlayer().isAlive() && world.areEnemiesAlive())
	{
		cout << (playerTurn ? "\n === PLAYER TURN ===\nUse WASD to move or Q to quit." : "\n=== ENEMY TURN ===");

		if (world.areEnemiesAdjacentToPlayer())
		{
			cout << "\nEnemy adjacent to player." << (playerTurn ? " Use X to attack!" : "");
		}

		if (playerTurn)
		{
			for (const Item& item : world.getItems())
			{
				if (world.getPlayer().getPosition() == item.getPosition() && playerTurn && !item.isCollected())
				{
					cout << "\nUse E to pick up the " << item.getName() << "!";
				}
			}

			if (world.getPlayer().getInventorySize() > 0)
			{
				cout << "\nUse U to use recently acquired loot.";
			}
		}
	}
	cout << endl;
}


