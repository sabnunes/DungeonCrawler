// LevelDescription class declaration

#pragma once
#include <string>
#include <vector>
#include "Enemy.h"

class LevelDescription
{
public:
    LevelDescription();
    explicit LevelDescription(int levelNum);

    int getLevel() const;
    std::string getName() const;
    std::vector<EnemyType> getEnemyTypes() const;
    int getItemCount(const int levelNum) const;

private:
    int levelNum = 0;
    std::string name;
    std::vector<EnemyType> enemies;
    int itemCount = getItemCount(levelNum);
};


