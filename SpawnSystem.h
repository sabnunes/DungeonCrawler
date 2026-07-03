#pragma once

/*
This includes:

Player spawn
Enemy spawn
Item spawn
Random position generation
Level enemy composition
Item count rules

This should eventually become a separate system because it depends on:

Map
Occupancy
Level definition
RNG

A clean portfolio design would separate “what level contains” from “how it is spawned.”

Right now, spawnEnemies() hardcodes level composition with a switch. That is okay for early learning, but it will scale badly.

Better direction:

Level 1:
  enemies: 1 slime
  items: 0

Level 2:
  enemies: 2 slimes
  items: 2

Level 3:
  enemies: 2 slimes, 1 leopard
  items: 2

This could be stored in a LevelDefinition struct. That would be much cleaner than adding more switch cases forever.
*/

class SpawnSystem
{
};

