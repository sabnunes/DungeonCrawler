Add screenshots.
Architecture diagram. - ref book on O'Reilly w/ diagrams, split:
behavior, 
explaining architecture and controls

Headers:
How to Play

Design Decisions

What I Learned
every design decision has an impact on what code needs to be implemented and everything becomes further intertwined the more a project complexity increases (ie if a player has health, how health is calculated when receiving dmg, how it is displayed/rendered, game win/loss scenarios
Starting from scratch
input/update/render loop in game
initial map, character, enemy, item setup
[...] check GitHub commit summaries



at some point where the game had a functional vertical slice, game.cpp was becoming chaotic, doing a lot. At first it was really hard to 
level names
map generation
enemy combinations
item counts
random item generation
player spawning
enemy spawning
item spawning
game loop
combat and combat rules
movement
rendering
inventory
input

refactored the architecture to include
Game broke out into: 
Gameworld
CombatSystems
LevelDefinition
EnemyBehavior
Renderer render() to draw:
stats
map
entities
messages

Game = orchestrates the game.
GameWorld = stores and manages the world's state.
EnemyBehavior = AI and decision-making.
CombatSystem = combat rules.
GridMap = terrain.
LevelDefinition = describes what a level should contain.

Game
│
├── Player
├── GameWorld
├── CombatSystem
├── EnemyBehavior
│
└── run()
└── input()
└── render()

GameWorld
│
├── GridMap
├── LevelDefinition
├── vector<Enemy>
├── vector<Item>
│
├── initializeLevel()
├── spawnEnemies()
├── spawnItems()
├── generateSpawnPos()
├── isOccupied()
└── areEnemiesAlive()

EnemyBehavior
│
├── takeTurn()
├── moveEnemy()
├── attackPlayer()
└── chooseDirection()

Game
│
├── runs game loop:
        │
        ├── run()
        ├── input()
        └── render()
├── owns Player
├── owns systems
│
├── CombatSystem
├── EnemyBehavior
└── GameWorld
        │
        ├── GridMap
        ├── LevelDescription
        ├── Enemies
        └── Items

Domain objects provide state.
Systems transform state.
Presentation formats results.
Input translates external input into commands.

Future work
I did not spend a lot of time thinking of the game design itself outside of attempting to make sure to cover ground around possible bugs encountered since will work with designers though I understand engineering may give opportunity for easy or difficult implementation of future design decisions. There is room for improvement around "fun" or "challenge" or even how the game is displayed within the console