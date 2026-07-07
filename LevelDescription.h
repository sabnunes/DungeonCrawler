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

    static constexpr int MAX_LEVEL = 5;

    int getLevel() const;
    const std::string& getName() const;
    const std::vector<EnemyType>& getEnemyTypes() const;
    int getItemCount() const;

private:
    int levelNum = 0;
    std::string name = "Level Name";
    std::vector<EnemyType> enemies;
    int itemCount = 0;
};


