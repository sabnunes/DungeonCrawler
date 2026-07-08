// Member function definitions for Game class
#include <iostream>
#include <random>
#include <iomanip>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
	: m_engine(std::random_device{}()) // Initialize the standard Mersenne Twister engine with the seed
{
	cout << "Welcome to DUNGEON CRAWLER\n" << endl;
	printLegend();

	nextLevel();	
} // end Game constructor

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

	col("W up");		col("s Slime");		col("H HP+10"); cout << "\n";
	col("A left");		col("l Leopard");	col("S STR++"); cout << "\n";
	col("S down");		col("d Doe");		col("D DEF++"); cout << "\n";

	col("D right");		col("");			col("");        cout << "\n";

	col("X attack");	col("");			col("");		cout << "\n";
	col("E equip");		col("ENVIRONMENT"); col("");		cout << "\n";
	col("U use loot");	col("^ tree");		col("~ water"); cout << "\n";
	col("Q quit");		col(", grass");		col("* rock");	cout << "\n";

	cout << "\n";
}

// Increments level to next level and triggers level intialization
void Game::nextLevel()
{
	currentLevel++;

	world.initializeLevel(currentLevel);

	printLevelName();

	playerTurn = true;
}

// Initializes player, enemies, and items
void Game::printLevelName()
{
	// Print level number and name
	cout << "\nLEVEL "
		 << world.getLevelDescription().getNumber()
		 << " "
		 << world.getLevelDescription().getName()
		 << endl << endl;
}

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
				cout << "You've defeated all enemies! NEXT LEVEL!" << endl;
				nextLevel();
			}
			else
			{
				cout << (world.getPlayer().isAlive() ? "You've defeated all enemies! You win!" : "You are dead. Game over.") << endl;
				running = 0;
			}
		}
	}
	cout << "Thanks for playing!" << endl;
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
		playerTurn = 0;
	}
}

// Update game state based on input and other factors, e.g., move enemies, check for collisions, update health, etc.
void Game::updateEnemies()
{
	// exit if no enemies alive
	if (!world.areEnemiesAlive())
	{
		return;
	}

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			// TO REMOVE - MOVED TO ENEMYBEHAVIOR with
			//enemyBehavior.takeTurn(enemy, player, map);

			if (world.isEnemyAdjacentToPlayer(enemy))
			{
				enemyAttack(enemy);
			}
			else
			{
				enemyMove(enemy);
			}
		}
	}	

	cout << endl; // empty line
	playerTurn = 1;
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
		std::cout << (playerTurn ? "\nYour turn. Use WASD to move or Q to quit." : "\nEnemy turn.") << endl;

		if (world.areEnemiesAdjacentToPlayer())
		{
			cout << "Enemy adjacent to player." << (playerTurn ? " Use X to attack!" : "") << endl;
		}

		for (const Item &item : world.getItems())
		{
			if (world.getPlayer().getPosition() == item.getPosition() && playerTurn && !item.isCollected())
			{
				cout << "Stumbled on item: " << item.getName() << "." << " Use E to pick up." << endl;
			}
		}

		if (world.getPlayer().getInventorySize() > 0)
		{
			cout << "Use U to use recently acquired loot." << endl;
		}
	}
	cout << endl;
}

// Move the player to a new position if it's valid and walkable, check for enemy collision
void Game::printPlayerMove(int x, int y)
{
	Position2D pos = world.getPlayer().getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (world.getMap().isWalkable(newPos) && !world.isOccupiedByEnemy(newPos))
	{
		cout << "You moved " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ". " << endl;
	}
	else if (world.getMap().isWalkable(newPos) && world.isOccupiedByEnemy(newPos)) // don't move if player is trying to move to enemy position
	{
		cout << "Cannot move there. Use X to attack or WASD to move." << endl;
	}
	else // if the tile is not walkable, print a message indicating the player cannot move in that direction
	{
		cout << "Cannot move " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ", tile is not walkable." << endl;
	}
	cout << endl; // empty line
}

// Enemy movement behavior and pattern
void Game::enemyMove(Enemy& enemy)
{
	// STUNED/IDLE LOGIC
	if (enemy.getStunnedState() == true)
	{
		enemy.setStunnedState(false);
		cout << enemy.getName() << " gathering its senses." << endl;
		return;
	}

	// FIND NEXT POS
	// x and y coordinate variables
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
		//cout << "DEBUG: ENEMY MOVE SLIME\n";
		uniform_int_distribution<int> range(-1, 1);

		do
		{
			x = range(m_engine);
			y = range(m_engine);
		} while (x == 0 && y == 0);

		break;
	}
	case EnemyType::Leopard:	// Moves towards player, incl. diagonals
		//cout << "DEBUG: ENEMY MOVE LEOPARD\n";
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

		std::cout << enemy.getName() << " moved "
			<< (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up")))
			<< ".\n";
	}
	// FAIL MOVE
	else
	{
		cout << enemy.getName() << " attempted move, but cannot move there!" << endl;
	}
}

// Player attacks enemy, enemy loses life if attack successful, check for enemy defeat
void Game::playerAttack()
{
	cout << "Attack enemy." << endl;
	bool successfulAttack = false;

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && world.isEnemyAdjacentToPlayer(enemy))
		{
			combatSystem.attack(world.getPlayer(), enemy);
			enemy.setStunnedState(false); // reset enemy movement pattern if attacked
			cout << "Attack successful. ";
			successfulAttack = true;

			if (!enemy.isAlive())
			{
				cout << enemy.getName() << " is dead! Strength increased +1." << endl;
				world.getPlayer().setStrength(world.getPlayer().getStrength() + 1); // increase player strength as a reward for defeating the enemy
			}
			else
			{
				cout << enemy.getName() << " lost " 
						<< combatSystem.calculateDamage(world.getPlayer(), enemy) << " HP." << endl;
				cout << enemy.getName() << " preparing counterattack." << endl;
			}
		}
	}
	
	if (!successfulAttack)
	{
		cout << "No enemy in range." << endl;
	}
}

// Enemy attacks player, player loses life if attack successful, check for player defeat
void Game::enemyAttack(Enemy& enemy)
{
	cout << enemy.getName() << " attacked you!" << endl;
	int damage = combatSystem.calculateDamage(enemy, world.getPlayer());

	if (damage)
	{
		// enemy attacks player
		combatSystem.attack(enemy, world.getPlayer());
		cout << enemy.getName() << " attack successful. You lost " 
			 << damage << " HP." << endl;

		if (!world.getPlayer().isAlive())
		{
			cout << "You died!" << endl;
		}
	}
	else
	{
		cout << enemy.getName() << " attack unsuccesful." << endl;
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
			cout << item.getName() << " acquired!" << endl;
			return;
		}

		if (!item.isCollected())
		{
			worldItemsExist = true;
		}
	}

	if (worldItemsExist)
	{
		cout << "To pick up an existing item, you must travel to its location." << endl;
	}
	else
	{
		cout << "No items exist." << endl;
	}
	cout << endl; // empty line
}

void Game::printPlayerUseItem()
{
	if (world.getPlayer().getInventorySize() > 0)
	{
		const Item &item = world.getPlayer().getInventoryItem();

		switch (item.getType())
		{
		case ItemType::HealthPotion: // give player +10 HP
			cout << "You've gained 10 HP!" << endl;
			break;
		case ItemType::StrengthPotion: // give player +1 STR
			cout << "You've gained 1 strength point!" << endl;
			break;
		case ItemType::DefensePotion: // give player +1 DEF
			cout << "You've gained 1 defense point!" << endl;
			break;
		default:
			cout << "unknown item used in printPlayerUserItem";
			break;
		}
	}
	else
	{
		cout << "You do not have any loot." << endl;
	}
	cout << endl; // empty line
}