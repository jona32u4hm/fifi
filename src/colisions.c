#include "colisions.h"
#include "raylib.h"

bool CheckPlayerEnemyCollision(Entity *player, Entity *enemy) {

    Rectangle r1 = player->dest_rect;
    Rectangle r2 = enemy->dest_rect;

    return CheckCollisionRecs(r1, r2);
}
