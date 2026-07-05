// LevelDefinition class declaration

#pragma once
#include <string>
#include <vector>
#include "Enemy.h"

class LevelDefinition
{
public:
    LevelDefinition();
    explicit LevelDefinition(int level);

    std::string getName() const;
    int getLevel() const;
	int getItemCount(const int level) const;
    
private:
    int level = 0;
    std::string name;
    std::vector<EnemyType> enemies;
    int itemCount = getItemCount(level);

};

