#include "raylib.h"
#include "colision.h"

bool CheckCollisionWithWalls(Rectangle player, Rectangle *walls, int wallCount) {
    for (int i = 0; i < wallCount; i++) {
        if (CheckCollisionRecs(player, walls[i])) {
            return true;
        }
    }
    return false;
}
