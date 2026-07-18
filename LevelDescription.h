// LevelDescription class declaration

#pragma once
#include <string>
#include <vector>
#include "Enemy.h"

class LevelDescription
{
public:
    LevelDescription();                         // default constructor
    explicit LevelDescription(int levelNumber); // parameterized constructor with level number

    static constexpr int MAX_LEVEL = 5;         // max levels that exist in the game

    // Getters that return level number, name, enemy types, and item count
    int getNumber() const;                                  
    const std::string& getName() const;                     
    const std::vector<EnemyType>& getEnemyTypes() const;
    int getItemCount() const;                               

private:
    int levelNumber = 0;
    std::string name = "Level Name";
    std::vector<EnemyType> enemies;    
    int itemCount = 0;

};


