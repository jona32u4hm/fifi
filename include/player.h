#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entities.h"   // Contains Direction, Textures, Entity
#include <math.h>
#include "game_data.h"
#include "colision_wall.h"


// alien guard parameters:
#define PLAYER_FOLLOW_RANGE 3*16


// --- MOVEMENT FUNCTIONS ---
void move_player(Entity* player, Camera2D* camera);
void move_alien_guard(Entity* alien, Entity* player, LevelData* currentLevel);

// --- CREATION FUNCTIONS ---
Entity initialize_player();

#endif // PLAYER_H

