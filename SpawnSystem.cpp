// Member function definitions for SpawnSystem class

//#include "SpawnSystem.h"
//
//// Constructor
//SpawnSystem::SpawnSystem()
//{
//}
//
//Position2D SpawnSystem::spawnPlayer()
//{
//	return generateSpawnPos();	// Generate spawn position for player
//}
//
//Position2D SpawnSystem::spawnEnemy()
//{
//}
//
//Position2D SpawnSystem::spawnItem()
//{
//}

//Position2D SpawnSystem::generateSpawnPos()
//{
//	// Generate a random position within the map bounds
//	std::uniform_int_distribution<int> distX(GridMap::START_POS_X, GridMap::WIDTH - 1);
//	std::uniform_int_distribution<int> distY(GridMap::START_POS_Y, GridMap::HEIGHT - 1);
//	Position2D pos;
//	do
//	{
//		pos.x = distX(m_engine);
//		pos.y = distY(m_engine);
//	} while (!map.isWalkable(pos) || isOccupied(pos)); // Ensure the position is walkable and not occupied
//	return pos;
//}
//Position2D SpawnSystem::generateSpawnPos()
//{
//	// Define the inclusive range [] for x and y; exclude walls
//	uniform_int_distribution<int> rangeX(1, map.getWidth() - 2);
//	uniform_int_distribution<int> rangeY(1, map.getHeight() - 2);
//
//	Position2D pos; // create a structure to hold the spawn position coordinates
//
//	// Generate random x and y coordinates for the spawn position, regenerate if not walkable
//	do
//	{
//		pos.x = rangeX(m_engine);
//		pos.y = rangeY(m_engine);
//	} while (!map.isWalkable(pos));
//
//	return pos; // return the generated spawn position coordinates
//}
