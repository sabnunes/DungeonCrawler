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
	player.setPosition(world.getPlayerSpawnPosition());	// Sets player spawn position
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
		if (player.isAlive() && playerTurn)
		{
			input();
		}
		else if (areEnemiesAlive() && !playerTurn)
		{
			updateEnemies();
		}
		else
		{
			if (player.isAlive() && currentLevel < LevelDescription::MAX_LEVEL)
			{
				cout << "You've defeated all enemies! NEXT LEVEL!" << endl;
				nextLevel();
			}
			else
			{
				cout << (player.isAlive() ? "You've defeated all enemies! You win!" : "You are dead. Game over.") << endl;
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
				playerMove(0, -1);
				break;
			case 'a':
				// Move player left x--
				playerMove(-1, 0);
				break;
			case 's':
				// Move player down y++
				playerMove(0, 1);
				break;
			case 'd':
				// Move player right x++
				playerMove(1, 0);
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
				playerPickUpItem();
				break;
			case 'u':
				playerUseItem();
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
	if (!areEnemiesAlive())
	{
		return;
	}

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			// TO REMOVE - MOVED TO ENEMYBEHAVIOR with
			//enemyBehavior.takeTurn(enemy, player, map);

			if (isLiveEnemyAdjacentToPlayer(enemy))
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
		<< right << setw(3) << player.getHealth() << " HP  "
		<< setw(2) << player.getStrength() << " STR  "
		<< setw(2) << player.getDefense() << " DEF";
	if (playerTurn && player.getInventorySize() > 0)
	{
		cout << "  LOOT ";
		player.printInventory();
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
			if (player.getPosition() == pos && player.isAlive())
			{
				cout << player.getIcon(); // print player icon if player is at this coordinate
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

	if (player.isAlive() && areEnemiesAlive())
	{
		std::cout << (playerTurn ? "\nYour turn. Use WASD to move or Q to quit." : "\nEnemy turn.") << endl;

		if (areAnyLiveEnemyAdjacentToPlayer())
		{
			cout << "Enemy adjacent to player." << (playerTurn ? " Use X to attack!" : "") << endl;
		}

		for (const Item &item : world.getItems())
		{
			if (player.getPosition() == item.getPosition() && playerTurn && !item.isCollected())
			{
				cout << "Stumbled on item: " << item.getName() << "." << " Use E to pick up." << endl;
			}
		}

		if (player.getInventorySize() > 0)
		{
			cout << "Use U to use recently acquired loot." << endl;
		}
	}
	cout << endl;
}

// Move the player to a new position if it's valid and walkable, check for enemy collision
void Game::playerMove(int x, int y)
{
	Position2D pos = player.getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (world.getMap().isWalkable(newPos) && !isOccupiedByEnemy(newPos))
	{
		player.setPosition(Position2D{ newPos.x, newPos.y });
		cout << "You moved " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ". " << endl;
	}
	else if (world.getMap().isWalkable(newPos) && isOccupiedByEnemy(newPos)) // don't move if player is trying to move to enemy position
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
		x = player.getPosition().x > enemy.getPosition().x ? 1 : -1;
		y = player.getPosition().y > enemy.getPosition().y ? 1 : -1;
		break;
	case EnemyType::Doe:		// Moves away from player
	{
		x = player.getPosition().x < enemy.getPosition().x ? 1 : -1;
		y = player.getPosition().y < enemy.getPosition().y ? 1 : -1;
		break;
	}
	default:
		break;
	}

	// VAR TO HOLD POS AND NEXT POS
	Position2D pos = enemy.getPosition();
	Position2D nextPos = { pos.x + x, pos.y + y };

	// PROVIDE 2 ADDTL ALT POS
	if (isOccupied(nextPos))
	{
		Position2D xOnly = { pos.x + x, pos.y };

		if (!isOccupied(xOnly))
		{
			nextPos = xOnly;
		}
		else
		{
			Position2D yOnly = { pos.x, pos.y + y };

			if (!isOccupied(yOnly))
			{
				nextPos = yOnly;
			}
		}
	}
	 
	// VALIDATE & MOVE TO NEXT POS
	if (!isOccupied(nextPos))
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

// Check if the enemy and player are in adjacent tiles (including diagonals)
bool Game::isLiveEnemyAdjacentToPlayer(const Enemy &enemy) const
{
	// get player and enemy positions
	Position2D playerPos = player.getPosition();

	// Check all adjacent positions around the player for the enemy's position
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) 
		{
			if (!(x == 0 && y == 0) && enemy.isAlive() && Position2D{ playerPos.x + x, playerPos.y + y } == enemy.getPosition())
			{
				return true; // Enemy is adjacent to the player
			}
		}
	}

	return false;
}

bool Game::areAnyLiveEnemyAdjacentToPlayer() const
{
	for (const Enemy& enemy : world.getEnemies())
	{
		// get player and enemy positions
		Position2D playerPos = player.getPosition();

		// Check all adjacent positions around the player for the enemy's position
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++)
			{
				if (!(x == 0 && y == 0) && enemy.isAlive() && Position2D { playerPos.x + x, playerPos.y + y } == enemy.getPosition())
				{
					return true; // Enemy is adjacent to the player
				}
			}
		}
	}	

	return false;
}

// Player attacks enemy, enemy loses life if attack successful, check for enemy defeat
void Game::playerAttack()
{
	cout << "Attack enemy." << endl;
	bool successfulAttack = false;

	for (Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && isLiveEnemyAdjacentToPlayer(enemy))
		{
			combatSystem.attack(player, enemy);
			enemy.setStunnedState(false); // reset enemy movement pattern if attacked
			cout << "Attack successful. ";
			successfulAttack = true;

			if (!enemy.isAlive())
			{
				cout << enemy.getName() << " is dead! Strength increased +1." << endl;
				player.setStrength(player.getStrength() + 1); // increase player strength as a reward for defeating the enemy
			}
			else
			{
				cout << enemy.getName() << " lost " 
						<< combatSystem.calculateDamage(player, enemy) << " HP." << endl;
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
	int damage = combatSystem.calculateDamage(enemy, player);

	if (damage)
	{
		// enemy attacks player
		combatSystem.attack(enemy, player);
		cout << enemy.getName() << " attack successful. You lost " 
			 << damage << " HP." << endl;

		if (!player.isAlive())
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
void Game::playerPickUpItem()
{
	bool worldItemsExist = false;

	for (Item& item : world.getItems())
	{
		if (item.getPosition() == player.getPosition() && !item.isCollected())
		{
			cout << item.getName() << " acquired!" << endl;
			item.collect();
			player.addInventoryItem(item);
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

void Game::playerUseItem()
{
	if (player.getInventorySize() > 0)
	{
		const Item &item = player.getInventoryItem();

		switch (item.getType())
		{
		case ItemType::HealthPotion: // give player +10 HP
			player.setHealth(player.getHealth() + 10);
			cout << "You've gained 10 HP!" << endl;
			break;
		case ItemType::StrengthPotion: // give player +1 STR
			player.setStrength(player.getStrength() + 1);
			cout << "You've gained 1 strength point!" << endl;
			break;
		case ItemType::DefensePotion: // give player +1 DEF
			player.setDefense(player.getDefense() + 1);
			cout << "You've gained 1 defense point!" << endl;
			break;
		default:
			cout << "unknown item used in playerUseItem";
			break;
		}
		
		player.useInventoryItem();
	}
	else
	{
		cout << "You do not have any loot." << endl;
	}
	cout << endl; // empty line
}


bool Game::isOccupied(const Position2D &pos) const
{
	// Map
	if (!world.getMap().isWalkable(pos))
	{
		return true;
	}

	// Player
	if (pos == player.getPosition())
	{
		return true;
	}

	// Enemies
	for (const Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && pos == enemy.getPosition())
		{
			return true;
		}
	}
		
	// Items
	for (const Item& item : world.getItems())
	{
		if (!item.isCollected() && item.getPosition() == pos)
		{
			return true;
		}
	}

	return false;
}

bool Game::isOccupiedByEnemy(const Position2D& pos) const
{
	for (const Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive() && pos == enemy.getPosition())
		{
			return true;
		}
	}

	return false;
}

// Returns if any enemies are alive
bool Game::areEnemiesAlive() const
{
	for (const Enemy& enemy : world.getEnemies())
	{
		if (enemy.isAlive())
		{
			return true;
		}
	}
	return false;
}
