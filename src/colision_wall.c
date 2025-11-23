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


int CheckPlayerCollision(LevelData *level, Entity* player) {

    float left   = player->dest_rect.x - player->dest_rect.width/2;
    float right  = player->dest_rect.x + player->dest_rect.width/2;
    float top    = player->dest_rect.y - player->dest_rect.height/2;
    float bottom = player->dest_rect.y + player->dest_rect.height/2;

    if (CheckMapCollision(level, left, top))    return 1;
    if (CheckMapCollision(level, right, top))   return 1;
    if (CheckMapCollision(level, left, bottom)) return 1;
    if (CheckMapCollision(level, right, bottom))return 1;

    return 0;
}
