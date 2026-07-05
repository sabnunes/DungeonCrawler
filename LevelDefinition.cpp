// Member function definitions for LevelDefinition class
#include "LevelDefinition.h"

// Default constructor
LevelDefinition::LevelDefinition() 
{

}

// Parameterized constructor
LevelDefinition::LevelDefinition(int level) 
	: level(level) 
{
	switch (level)
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
			break;
	}
} // End of constructors

int LevelDefinition::getLevel() const
{
	return level;
}

int LevelDefinition::getItemCount(const int level) const
{
	return level == 1 ? 0 : 1 + level / 2;
}