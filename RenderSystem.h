// Render system class declaration
#pragma once
#include "Direction.h"
#include "GameWorld.h"
#include "LevelDescription.h"
#include "EnemyBehavior.h"

class RenderSystem
{
public:
	RenderSystem();

	void render(const GameWorld& world, bool playerTurn) const;	// main function that prints repeated loop output: character stats, inventory, map, and status messages
	
	void printHeader() const;									// prints game title
	void printLegend() const;									// prints the legend including controls, enemies, obstacles
	void printSeed(unsigned seed) const;						// prints game seed
	void printLevel(const LevelDescription& level) const; 		// prints level number and name
	void printNextLevel() const;								// prints level win

	void printInvalidInput() const;								// prints invalid player input

	// print player action results: move, attack, collect item, and use item
	void printPlayerMove(const GameWorld& world, const PlayerMoveResult& moveResult) const;					
	void printPlayerAttack(const Enemy* enemy, const CombatResult& result, const bool successfulAttack) const;
	void printPlayerCollectItem(const PlayerCollectedItem& itemCollected) const;							
	void printPlayerUseItem(const Item* item) const;

	// prints enemy turn result: attack or move
	void printEnemyTurn(const Enemy& enemy, const EnemyTurnResult& result) const;

	void printGameEnd(bool won) const;							// prints game end: win or loss
	void printGoodbye() const;									// prints goodbye
	//void printGameOver() const;

private:
	void renderStats(const GameWorld& world) const;				// prints character stats (player, enemies)
	void renderPlayerInventory(const GameWorld& world) const;	// prints player inventory
	void renderMap(const GameWorld& world) const;				// renders map
	void renderStatusMessages(const GameWorld& world, const bool playerTurn) const; // renders game status messages like player/enemy turn, adjacent to enemy, overlapping item

};

