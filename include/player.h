#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entities.h"   // Contains Direction, Textures, Entity

// --- MOVEMENT FUNCTIONS ---
void move_player(Entity* player, Camera2D* camera);
void move_alien(Entity* alien);

// --- CREATION FUNCTIONS ---
Entity initialize_player();
Entity CreateAlien();

#endif // PLAYER_H

