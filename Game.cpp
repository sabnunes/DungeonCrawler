// Member function definitions for Game class
#include <iostream>
#include <random>
#include <iomanip>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
{
	cout << "Welcome to DUNGEON CRAWLER\n" << endl;
	printLegend();

	nextLevel();	
} // end Game constructor

// run the game: welcome message, process main game loop (input, update, render)
void Game::run()
{
	running = true; // set running flag to true to start the game loop

	while (running)
	{
		render();

		if (world.getPlayer().isAlive() && playerTurn)
		{
			input();
		}
		else if (world.areEnemiesAlive() && !playerTurn)
		{
			updateEnemies();
		}
		else
		{
			if (world.getPlayer().isAlive() && currentLevel < LevelDescription::MAX_LEVEL)
			{
				cout << "\n";
				cout << "You've defeated all enemies! NEXT LEVEL!\n\n";

				nextLevel();
			}
			else
			{
				cout << (world.getPlayer().isAlive() ? "You've defeated all enemies! You win!" : "You are dead. Game over.") << endl;
				running = false;
			}
		}
	}
	cout << "Thanks for playing!" << endl;
}

// Increments level to next level and triggers level intialization
void Game::nextLevel()
{
	currentLevel++;

	world.initializeLevel(currentLevel);

	printLevelName();

	playerTurn = true;
}

// Get player input and process it, e.g., move player position, update health, etc
void Game::input()
{
	// Prompt the user for input
	char input;
	cout << "Enter input: ";
	cin >> input;

	// Convert input to lowercase for case-insensitive processing
	input = tolower(input);

	if (playerTurn)
	{
		// Process and verify input for movement and quitting
		switch(input)
		{
			case 'w':
				// Move player up y--
				printPlayerMove(0, -1);
				world.playerMove(0, -1);
				break;
			case 'a':
				// Move player left x--
				printPlayerMove(-1, 0);
				world.playerMove(-1, 0);
				break;
			case 's':
				// Move player down y++
				printPlayerMove(0, 1);
				world.playerMove(0, 1);
				break;
			case 'd':
				// Move player right x++
				printPlayerMove(1, 0);
				world.playerMove(1, 0);
				break;
			case 'x':
				// Attack the enemy if they are in an adjacent tile (check for enemy position relative to player position)
				playerAttack();
				break;
			case 'q':
				// Quit the game
				running = false;
				break;
			case 'e':
				printPlayerPickUpItem();
				world.playerPickUpItem();
				break;
			case 'u':
				printPlayerUseItem();
				world.playerUseItem();
				break;
			default:
				cout << "Invalid input. Use WASD keys to move, Q to quit.\n" << endl;
				break;
		}
		cout << endl;

		playerTurn = false;
	}
}

// Update game state based on input and other factors, e.g., move enemies, check for collisions, update health, etc.
void Game::updateEnemies()
{
	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			EnemyTurnResult enemyTurnResult = enemyBehavior.takeTurn(enemy, world, combatSystem);
			printEnemyTurnResult(enemy, enemyTurnResult);
		}
	}	
	cout << endl;

	playerTurn = true;
}

// Render game state to the screen,	display player health, inventory, etc., display game world, enemies, etc.
void Game::render()
{
	// Print player and enemy stats
	cout << left << setw(8) << "Player"
		<< right << setw(3) << world.getPlayer().getHealth() << " HP  "
		<< setw(2) << world.getPlayer().getStrength() << " STR  "
		<< setw(2) << world.getPlayer().getDefense() << " DEF";
	if (playerTurn && world.getPlayer().getInventorySize() > 0)
	{
		cout << "  LOOT ";
		world.getPlayer().printInventory();
	}
	cout << endl;

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
				
					for (const Item &item : world.getItems())
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

	if (world.getPlayer().isAlive() && world.areEnemiesAlive())
	{
		cout << (playerTurn ? "\n === PLAYER TURN ===\nUse WASD to move or Q to quit." : "\n=== ENEMY TURN ===");

		if (world.areEnemiesAdjacentToPlayer())
		{
			cout << "\nEnemy adjacent to player." << (playerTurn ? " Use X to attack!" : "");
		}

		if (playerTurn)
		{
			for (const Item &item : world.getItems())
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

// Player attacks enemy, enemy loses life if attack successful, check for enemy defeat
void Game::playerAttack()
{
	Player& player = world.getPlayer();

	cout << "You attempt an attack on the enemy." << endl;
	bool successfulAttack = false;

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && world.isEnemyAdjacentToPlayer(enemy))
		{
			CombatResult attackResult = combatSystem.attack(player, enemy);

			enemy.setStunnedState(false); // reset enemy movement pattern if attacked

			cout << "You slash the " << enemy.getName() << "!";

			successfulAttack = true;

			if (attackResult.killed)
			{
				cout << enemy.getName() << " is dead! Strength increased +1." << endl;
				player.modifyStrength(1); // increase player strength as a reward for defeating the enemy
			}
			else
			{
				cout << attackResult.damage << " damage dealt." << endl;
				cout << enemy.getName() << " preparing counterattack." << endl;
			}
		}
	}

	if (!successfulAttack)
	{
		cout << "No enemy in range." << endl;
	}
}

// Prints the legend for the game, including controls, enemies, and environment obstacles
void Game::printLegend()
{
	cout << "Legend\n";
	cout << left;

	auto col = [](const string& text)
		{
			cout << setw(12) << text;
		};

	col("CONTROLS");	col("ENEMIES");		col("LOOT");	cout << "\n";
	col("W north");		col("s Slime");		col("H HP+10"); cout << "\n";
	col("A west");		col("l Leopard");	col("S STR++"); cout << "\n";
	col("S south");		col("d Doe");		col("D DEF++"); cout << "\n";
	col("D east");		col("");			col("");        cout << "\n";
	col("X attack");	col("");			col("");		cout << "\n";
	col("E equip");		col("ENVIRONMENT"); col("");		cout << "\n";
	col("U use loot");	col("^ tree");		col("~ water"); cout << "\n";
	col("Q quit");		col(", grass");		col("* rock");	cout << "\n";

	cout << endl;
}

// Initializes player, enemies, and items
void Game::printLevelName()
{
	// Print level number and name
	cout << "\n---------------------------------\n LEVEL "
		<< world.getLevelDescription().getNumber()
		<< " "
		<< world.getLevelDescription().getName()
		<< "\n---------------------------------"
		<< endl << endl;
}

// Move the player to a new position if it's valid and walkable, check for enemy collision
void Game::printPlayerMove(int x, int y)
{
	Position2D pos = world.getPlayer().getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (world.getMap().isWalkable(newPos) && !world.isOccupiedByEnemy(newPos))
	{
		cout << "You moved " << (x > 0 ? "east" : (x < 0 ? "west" : (y > 0 ? "south" : "north"))) << ". " << endl;
		
		for (const Item& item : world.getItems())
		{
			if (newPos == item.getPosition() && !item.isCollected())
			{
				cout << "You found a " << item.getName() << "! Pick it up on your next turn." << endl;
			}
		}
	}
	else if (world.getMap().isWalkable(newPos) && world.isOccupiedByEnemy(newPos)) // don't move if player is trying to move to enemy position
	{
		cout << "Cannot move there. Use X to attack or WASD to move." << endl;
	}
	else // if the tile is not walkable, print a message indicating the player cannot move in that direction
	{
		cout << "Cannot move " << (x > 0 ? "east" : (x < 0 ? "west" : (y > 0 ? "south" : "north"))) << ", tile is not walkable." << endl;
	}
}

// Marks item as picked up if player overlaps same position as item
void Game::printPlayerPickUpItem()
{
	bool worldItemsExist = false;

	for (Item& item : world.getItems())
	{
		if (item.getPosition() == world.getPlayer().getPosition() && !item.isCollected())
		{
			cout << item.getName() << " added to inventory!" << endl;
			return;
		}

		if (!item.isCollected())
		{
			worldItemsExist = true;
		}
	}

	if (worldItemsExist)
	{
		cout << "To pick up an item, you must travel to its location.";
	}
	else
	{
		cout << "No items exist.";
	}

	cout << endl;
}

void Game::printPlayerUseItem()
{
	if (world.getPlayer().getInventorySize() > 0)
	{
		const Item &item = world.getPlayer().getInventoryItem();

		switch (item.getType())
		{
		case ItemType::HealthPotion: // give player +HP
			cout << "You've gained " << item.getValue() << " HP by consuming the " << item.getName() <<"!" << endl;
			break;
		case ItemType::StrengthPotion: // give player +STR
			cout << "You've gained " << item.getValue() << " strength point by consuming the " << item.getName() << "!" << endl;
			break;
		case ItemType::DefensePotion: // give player +1 DEF
			cout << "You've gained " << item.getValue() << " defense point by consuming the " << item.getName() << "!" << endl;
			break;
		default:
			cout << "unknown item used in printPlayerUserItem" << endl;
			break;
		}
	}
	else
	{
		cout << "You do not have any loot." << endl;
	}
}

// Enemy attacks player, player loses life if attack successful, check for player defeat
void Game::printEnemyTurnResult(Enemy& enemy, EnemyTurnResult& enemyTurnResult)
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
			cout << enemy.getName() << " attack unsuccesful." << endl;
		}
	}
	else
	{
		if (enemy.getStunnedState() == true)
		{
			cout << enemy.getName() << " gathering its senses." << endl;
			return;
		}

		if (enemyTurnResult.moved)
		{
			cout << enemy.getName() << " moved "
				 << (enemyTurnResult.deltaPos.x > 0 ? "east" 
				  : (enemyTurnResult.deltaPos.x < 0 ? "west" 
				  : (enemyTurnResult.deltaPos.y > 0 ? "south" : "north")))
				 << "." << endl;
		}
		else
		{
			cout << enemy.getName() << " attempted move, but cannot move there!" << endl;
		}
	}
}