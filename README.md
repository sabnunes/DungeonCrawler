# DUNGEON CRAWLER v1.0      

Survive through five increasingly difficult dungeon levels to defeat all enemies.

A C++20 console roguelike created to demonstrate object-oriented programming, game architecture, AI behaviors, and turn-based game systems.

## Features
- Three enemy types with unique AI behaviors
- Player health, strength, and defense progression
- Collectible and consumable potions
- Five crafted dungeon levels
- Turn-based tactical combat
- Console map rendering

## How to Play
Explore each dungeon level, defeat every enemy to progress, and survive long enough to clear all five levels.

### Player Turn
- Use WASD to move
- Use X to attack adjacent enemies
- Use E when standing on loot to add it to your inventory
- Use U to consume the most recently collected potions
- Use Q to quit.

P represents the player's position on the map.

### Enemy Types
| Enemy | Behavior |
|:------|:---------|
| Slime | Wanders randomly around the map. |
| Leopard | Aggressively hunts the player. |
| Doe | Flees when the player gets too close. |

### Legend

| **Controls** | **Enemies** | **Terrain** |
|:-------------|:-------------------|:-------------------|
| W North      | s Slime            | ^ Tree             |
| A West       | l Leopard          | , Grass            |
| S South      | d Doe              | ~ Water            |
| D East       |                    | \* Rock            |
| X Attack     |**Loot**            |                    |
| E Pick Up    | H HP +10           |                    |
| U Use Loot   | S STR +1           | **Hero**           |
| Q Quit       | D DEF +1           | P Player           |

## Build Requirements
This project was developed with:
- Microsoft Visual Studio 2022 (Version 17.14.36)
- ISO C++20 Standard

If necessary, configure the project using:

`Solution Properties → C/C++ → Language → C++ Language Standard → ISO C++20 Standard (/std:c++20)`

## Architecture

### Loop
| Class | Responsibility |
|-------|----------------|
| Game | Main game loop, input handling, and turn management |

### Systems
| Class | Responsibility |
|-------|----------------|
| GameWorld | Owns the map, entities, and game state |
| CombatSystem | Calculates attack damage and combat outcomes |
| EnemyBehavior | Controls enemy AI, movement, and decision making |
| RenderSystem | Renders game world and player feedback |

### World
| Class | Responsibility |
|-------|----------------|
| GridMap | Stores the dungeon layout and terrain information |
| LevelDescription | Defines level themes and enemy/item counts |

### Data
| Class | Responsibility |
|-------|----------------|
| Entities | Core gameplay entities |
| ├── Character | Shared health, stats, and position for living entities |
| │   ├── Player | Player-controlled character with inventory and progression |
| │   └── Enemy | AI-controlled character with unique behaviors |
| └── Item | Collectible consumables that modify player statistics |

## My Learnings
- Each game feature quickly increased the complexity of associated systems.
- Interconnected systems often require changes across multiple classes when adding new functionality..
- Separating responsibilities into focused classes greatly improves readability and maintainability.
- Incremental refactoring proved safer and easier to debug than large-scale refactoring changes.
- Frequent testing helped catch regressions sooner than later when complexity increased.

### Future Improvements
- Procedurally generated dungeons
- Additional enemy types and abilities
- Expanded item variety
- Equipment, and armor system
- Attack missed/failed %
- Save and load functionality
- Main menu and game restart

### Known Issues
- Certain random map seeds can generate inaccessible areas, preventing the player from reaching every enemy and completing the level.
- The legend may eventually scroll off the console after extended gameplay due to console output limitations.
- A Doe may remain in corner of the map.
