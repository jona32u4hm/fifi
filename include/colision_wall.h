#ifndef COLISION_WALL_H
#define COLISION_WALL_H

#include "game_data.h"

// Verifica si un punto px, py toca una pared (tile == 1)
int CheckMapCollision(LevelData *level, float px, float py);

// Colisión del jugador
int CheckPlayerCollision(LevelData *level, Entity* player);

//Colisión de entidades
int CheckEntityCollision(LevelData *level, Entity* e);

#endif
