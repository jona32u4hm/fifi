#ifndef UPDATE_ENTITIES_H
#define UPDATE_ENTITIES_H

#include "entities.h"

Camera2D initialize_camera(); 
void update_entities(Camera2D* camera, Entity* player, Entity* alien, Entity* melee, entity_array* proj_array, float* cooldown_proj, float* cooldown_melee);

#endif

