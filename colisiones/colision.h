#ifndef COLISION_H
#define COLISION_H

#include "raylib.h"

bool CheckCollisionWithWalls(Rectangle player, Rectangle *walls, int wallCount);

#endif
