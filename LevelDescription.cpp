// Member function definitions for LevelDescription class
#include "LevelDescription.h"

// Default constructor
LevelDescription::LevelDescription() 
{
}

// Parameterized constructor
LevelDescription::LevelDescription(int levelNum) 
	: levelNumber(levelNum) 
{
	itemCount = levelNum == 1 ? 0 : 1 + levelNum / 2;

	switch (levelNum)
	{
		case 1:
			name = "- The First Clearing";
			enemies = { 
				EnemyType::Slime 
			};
			break;
		case 2:
			name = "- The Boulder's Rest";
			enemies = { 
				EnemyType::Slime, 
				EnemyType::Slime 
			};
			break;
		case 3:
			name = "- The Lost Woods";
			enemies = { 
				EnemyType::Slime, 
				EnemyType::Slime, 
				EnemyType::Leopard 
			};
			break;
		case 4:
			name = "- The Sunken Pass";
			enemies = { 
				EnemyType::Doe 
			};
			break;
		case 5:
			name = "- The Ancient Grove";
			enemies = { 
				EnemyType::Slime, 
				EnemyType::Slime, 
				EnemyType::Slime, 
				EnemyType::Leopard, 
				EnemyType::Leopard, 
				EnemyType::Doe 
			};
			break;
		default:
			name = "Unknown Level";
			itemCount = 0;
			enemies.clear();
			break;
	}
} // End of constructors

int LevelDescription::getNumber() const
{
	return levelNumber;
}

const std::string& LevelDescription::getName() const
{
	return name;
}

const std::vector<EnemyType>& LevelDescription::getEnemyTypes() const
{
	return enemies;
}

int LevelDescription::getItemCount() const
{
	return itemCount;
}
