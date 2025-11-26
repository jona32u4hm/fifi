#include "colision_wall.h"
#include <stdio.h>

#define TILE_SIZE 16

int CheckMapCollision(LevelData *level, float px, float py) {

    int tileX = (int)(px / TILE_SIZE);
    int tileY = (int)(py / TILE_SIZE);

    // verifica límites
    if (tileX < 0 || tileX >= level->mapWidth ||
        tileY < 0 || tileY >= level->mapHeight) {
        return 1; // fuera del mapa = colisión
    }

    byte tile = level->map[tileY][tileX];

    return (tile == 1);
}


int CheckEntityCollision(LevelData *level, Entity* e) {

    float left   = e->dest_rect.x;
    float right  = e->dest_rect.x + e->dest_rect.width - 2;
    float top    = e->dest_rect.y;
    float bottom = e->dest_rect.y + e->dest_rect.height - 2;

    if (CheckMapCollision(level, left, top))    return 1;
    if (CheckMapCollision(level, right, top))   return 1;
    if (CheckMapCollision(level, left, bottom)) return 1;
    if (CheckMapCollision(level, right, bottom))return 1;

    return 0;
}

int CheckPlayerCollision(LevelData *level, Entity* player) {
    return CheckEntityCollision(level, player);
}