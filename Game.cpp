// Member function definitions for Game class
#include <iostream>
#include <random>
#include "Game.h"

using namespace std;

// Constructor
Game::Game()
	: m_engine(std::random_device{}()) // Initialize the standard Mersenne Twister engine with the seed
{
	//cout << "[DEBUG] Initializing map..." << endl;
	map.initialize();	// initializes the map
	//cout << "[DEBUG] Spawning elements..." << endl;
	initWorld();		// initializes player, enemies, items
	//cout << "[DEBUG] Constructor finished successfully!" << endl;


} // end Game constructor

// Initializes player, enemies, and items
void Game::initWorld()
{
	spawnPlayer();	// Spawns player
	spawnEnemies();	// Spawns enemies
	spawnItems();	// Spawns items
}

// Spawns player
void Game::spawnPlayer()
{
	Position2D spawnPos; 						// Create Position2D for player
	spawnPos = generateSpawnPos();				// Generate spawn position for player
	player.setPosition(spawnPos.x, spawnPos.y);	// Set player position to generated spawn position
}

// Spawns enemies
void Game::spawnEnemies()
{
	enemies.clear();

	// Spawn all enemies
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		// New enemy
		Enemy enemy(EnemyType::Doe);

		// Create Position2D
		Position2D spawnPos;

		// Generate spawn position until position not equal to player or existing enemy position
		do
		{
			spawnPos = generateSpawnPos();
		} while (isOccupied(spawnPos));

		// Set item position to generated spawn position
		enemy.setPosition(spawnPos.x, spawnPos.y);

		// Add item to world items
		enemies.push_back(enemy);
	}
}

// Spawns items
void Game::spawnItems()
{
	worldItems.clear();

	uniform_int_distribution<int> itemTypeRange(ITEM_TYPE_RANGE_MIN, ITEM_TYPE_RANGE_MAX);

	// Spawn all items
	for (int i = 0; i < ITEM_COUNT; i++)
	{
		// New item
		Item item;

		// Set item type
		item.setType(
			static_cast<ItemType>(itemTypeRange(m_engine))
		);

		// Create Position2D for item
		Position2D spawnPos;

		// Generate spawn position for item until position not equal to player or enemy position
		do
		{
			spawnPos = generateSpawnPos();
		} while (isOccupied(spawnPos));

		// Set item position to generated spawn position
		item.setPosition(spawnPos.x, spawnPos.y);

		// Add item to world items
		worldItems.push_back(item);
	}
}

// run the game: welcome message, process main game loop (input, update, render)
void Game::run()
{
	cout << "Welcome to DUNGEON CRAWLER\n" << endl;
	//cout << "Menu :\n1. Start Game\n2. Quit\nEnter your choice: ";

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
			update();
		}
		else
		{
			cout << (player.isAlive() ? "You've defeated all enemies! You win!" : "You are dead. Game over.") << endl;
			running = 0;
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
void Game::update()
{
	// exit if no enemies alive
	if (!areEnemiesAlive())
	{
		return;
	}

	for (Enemy& enemy : enemies)
	{
		if (isEnemyAdjacentToPlayer(enemy))
		{
			enemyAttack(enemy);
		}
		else
		{
			enemyMove(enemy);
		}
	}	

	cout << endl; // empty line
	playerTurn = 1;
}

// Render game state to the screen,	display player health, inventory, etc., display game world, enemies, etc.
void Game::render()
{
	// Print player and enemy stats
	printf("Player  %3d HP  %2d STR  %2d DEF  LOOT: ", 
		player.getHealth(), player.getStrength(), player.getDefense());
	player.printInventory();
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive())
		{
			printf("%-7s %3d HP  %2d STR  %2d DEF\n",
				enemy.getName().c_str(), enemy.getHealth(), enemy.getStrength(), enemy.getDefense());
		}
	}	
	cout << endl; // empty line

	// Render the grid map with the player icon
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++) {
			// PLAYER
			if (player.getPosition() == Position2D{ x, y } && player.isAlive())
			{
				cout << player.getIcon(); // print player icon if player is at this coordinate
			}
			// ENEMY
			else
			{
				bool enemyDrawn = false;

				for (const Enemy& enemy : enemies)
				{
					if (enemy.isAlive() && enemy.getPosition() == Position2D{ x,y })
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
				
					for (const Item &item : worldItems)
					{
						if (!item.isCollected() &&
							item.getPosition() == Position2D{ x, y })
						{
							cout << item.getIcon();
							itemDrawn = true;
							break;
						}
					}

					// TILE
					if (!itemDrawn)
					{
						cout << map.getTileIcon(x, y);
					}

				}
			}
		}
		cout << endl; // New line after each row
	}

	if (player.isAlive() && areEnemiesAlive())
	{
		printf("\n%s\n", playerTurn ? "Your turn. Use WASD to move or Q to quit." : "Enemy turn.");
		printf("Enemy adjacent to player? %s.%s\n", 
			isAnyEnemyAdjacentToPlayer() ? "Yes" : "No", isAnyEnemyAdjacentToPlayer() && playerTurn ? " Use X to attack." : "");
		
		for (const Item &item : worldItems)
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


// Generate a random walkable coordinate and assign it to the player
Position2D Game::generateSpawnPos()
{

	// Define the inclusive range [] for x and y; exclude walls
	uniform_int_distribution<int> rangeX(1, map.getWidth() - 2);
	uniform_int_distribution<int> rangeY(1, map.getHeight() - 2);

	Position2D pos; // create a structure to hold the spawn position coordinates

	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
	do
	{
		pos.x = rangeX(m_engine);
		pos.y = rangeY(m_engine);
	} while (!map.isWalkable(pos.x, pos.y));

	return pos; // return the generated spawn position coordinates
}

// Move the player to a new position if it's valid and walkable, check for enemy collision
void Game::playerMove(int x, int y)
{
	Position2D pos = player.getPosition();
	Position2D newPos = Position2D{ pos.x + x, pos.y + y };

	// check if the tile is walkable before moving and not occupied by the enemy
	if (map.isWalkable(newPos.x, newPos.y) && !isOccupiedByEnemy(newPos))
	{
		player.setPosition(newPos.x, newPos.y);
		cout << "You moved " << (x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up"))) << ". " << endl;
	}
	else if (map.isWalkable(newPos.x, newPos.y) && isOccupiedByEnemy(newPos)) // don't move if player is trying to move to enemy position
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
	//enemy behavior ideas
	// idle for 2 turns
	// begin movement pattern
	// if attacked, move away from player, resets idle/movement pattern
	// movement ideas: 
	// + pattern
	// - or | pattern
	// 4 squares pattern (L,R,D,U)
	// random movement
	// chance of no movement

	// STUNED/IDLE LOGIC
	if (enemyStunnedTurnsCount <= ENEMY_STUNNED_TURNS)
	{
		enemyStunnedTurnsCount++;
		cout << enemy.getName() << " gathering its senses." << endl;
		return;
	}

	/*cout << "TYPE CHECK: " << enemy.getName()
		<< " enum=" << (int)enemy.getType() << endl;*/

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
		/*
		//calculateDistance();

		double bestDistance = -1.0;

		Position2D current = enemy.getPosition();
		Position2D bestMove =
		{
			enemy.getPosition().x,
			enemy.getPosition().y
		};

		for (const Position2D move : possibleMoves)
		{
			Position2D possibleMove =
			{
				current.x + move.x,
				current.y + move.y
			};

			if (isOccupied(possibleMove))
			{
				continue;
			}

			// Manhattan distance
			double distance = abs(possibleMove.x - player.getPosition().x) + abs(possibleMove.y - player.getPosition().y);

			if (distance > bestDistance)
			{
				bestDistance = distance;
				bestMove = possibleMove;
			}
		}

		x = bestMove.x;
		y = bestMove.y;
		*/

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
		enemy.setPosition(nextPos.x, nextPos.y);
		printf("%s moved %s.\n", enemy.getName().c_str(), x > 0 ? "right" : (x < 0 ? "left" : (y > 0 ? "down" : "up")));
	}
	// FAIL MOVE
	else
	{
		cout << enemy.getName() << " attempted move, but cannot move there!" << endl;
	}
}

// Check if the enemy and player are in adjacent tiles (including diagonals)
bool Game::isEnemyAdjacentToPlayer(Enemy enemy) const
{
	 /* check:
	 x:-1 y:-1 upper left
	 x:-1 y: 0 left
	 x:-1 y:+1 lower left
	 x: 0 y:-1 up
	 x: 0 y:+1 down
	 x:+1 y:-1 upper right
	 x:+1 y: 0 right
	 x:+1 y:+1 lower right */

	// get player and enemy positions
	Position2D playerPos = player.getPosition();

	// Check all adjacent positions around the player for the enemy's position
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) 
		{
			if (!(x == 0 && y == 0) && Position2D{ playerPos.x + x, playerPos.y + y } == enemy.getPosition())
			{
				return true; // Enemy is adjacent to the player
			}
		}
	}

	return false;
}

bool Game::isAnyEnemyAdjacentToPlayer() const
{
	for (const Enemy& enemy : enemies)
	{
		// get player and enemy positions
		Position2D playerPos = player.getPosition();

		// Check all adjacent positions around the player for the enemy's position
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++)
			{
				if (!(x == 0 && y == 0) && Position2D { playerPos.x + x, playerPos.y + y } == enemy.getPosition())
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
	// Implement attack logic here
	if (areEnemiesAlive() && isAnyEnemyAdjacentToPlayer())
	{
		for (Enemy& enemy : enemies)
		{
			if (isEnemyAdjacentToPlayer(enemy))
			{
				// player attacks enemy
				enemy.setHealth(enemy.getHealth() - player.getStrength());
				enemyStunnedTurnsCount = 0; // reset enemy movement pattern if attacked
				cout << "Attack successful. ";

				if (enemy.getHealth() <= 0)
				{
					cout << enemy.getName() << " is dead! Strength increased +1." << endl;
					player.setStrength(player.getStrength() + 1); // increase player strength as a reward for defeating the enemy
					// handle enemy defeat drop loot etc
				}
				else
				{
					cout << enemy.getName() << " lost " << player.getStrength() << " HP." << endl;
					cout << enemy.getName() << " preparing counterattack." << endl;
				}
			}
		}
	}
	else
	{
		cout << "No enemy in range. Invalid move." << endl;
	}
}

// Enemy attacks player, player loses life if attack successful, check for player defeat
void Game::enemyAttack(Enemy enemy)
{
	cout << enemy.getName() << " attacked you!" << endl;

	if (player.getHealth() > player.getHealth() - enemy.getStrength())
	{
		// enemy attacks player
		player.setHealth(player.getHealth() - enemy.getStrength());
		cout << enemy.getName() << " attack successful. You lost " << enemy.getStrength() << " HP." << endl;
		if (player.getHealth() <= 0)
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

	for (Item& item : worldItems)
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
	if (!map.isWalkable(pos.x, pos.y))
	{
		return true;
	}

	// Player
	if (pos == player.getPosition())
	{
		return true;
	}

	// Enemies
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive() && pos == enemy.getPosition())
		{
			return true;
		}
	}
		
	// Items
	for (const Item& item : worldItems)
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
	for (const Enemy& enemy : enemies)
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
	for (const Enemy& enemy : enemies)
	{
		if (enemy.isAlive())
		{
			return true;
		}
	}
	return false;
}
