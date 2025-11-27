#ifndef COLISIONS_H
#define COLISIONS_H

#include "entities.h"
#include <raylib.h>
#include <stdbool.h>

bool CheckPlayerEnemyCollision(Entity *player, Entity *enemy);

#endif
