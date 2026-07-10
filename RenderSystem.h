// Render system class declaration
#pragma once
#include "GameWorld.h"
#include "LevelDescription.h"
#include "EnemyBehavior.h"

class RenderSystem
{
public:
	RenderSystem();

	void render(const GameWorld& world, bool playerTurn) const;
	
	void printHeader() const;
	void printLegend() const; // Prints the legend for the game, including controls, enemies, obstacles
	void printLevel(const LevelDescription& level) const; 	// Print level number and name
	void printNextLevel() const;

	void printInvalidInput() const;

	void printPlayerMove(const GameWorld& world, int dx, int dy) const;
	void printPlayerAttack(const Enemy* enemy, const CombatResult& result, const bool successfulAttack) const;
	void printPlayerCollectItem(const ItemCollected& itemCollected) const;
	void printPlayerUseItem(const Item* item) const;

	void printEnemyTurn(const Enemy& enemy, const EnemyTurnResult& result) const;

	void printGameEnd(bool won) const;
	void printGoodbye() const;
	//void printGameOver() const;

private:
	void renderStats(const GameWorld& world, const bool playerTurn) const;
	void renderPlayerInventory(const GameWorld& world) const;
	void renderMap(const GameWorld& world) const;
	//void renderEnemies(const GameWorld& world) const;
	void renderStatusMessages(const GameWorld& world, const bool playerTurn) const;

};

