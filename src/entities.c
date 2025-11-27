#include <stdio.h>
#include <stdlib.h>
#include "entities.h"

entity_array init_ent_array(int capacity) {
    entity_array ent_array = (entity_array) {
        .cap = capacity,
        .data = malloc(capacity * sizeof(Entity)),
        .size = 0,
    };
    return ent_array;
}

Entity CreateAlien(int type, float x, float y) {
    // Load textures
    Texture2D alien_up   = LoadTexture("assets/pixelart/alien_up.png");
    Texture2D alien_side = LoadTexture("assets/pixelart/alien_side_0.png");
    Texture2D alien_down = LoadTexture("assets/pixelart/alien_down.png");

    // Initialize texture struct
    Textures alien_textures = (Textures){
        .texture_up = alien_up,
        .texture_side = alien_side,
        .texture_down = alien_down,
    };

    // Create and return the fully initialized entity
    Entity alien = (Entity){
        .vertical_direction = 1,
        .horizontal_direction = 1,
        .current_direction = 2,
        .textures = alien_textures,
        .current_texture = alien_textures.texture_down,
        .hp = 10.0f,
        .i_time = 0.0f,
        .type = type,
        .dest_rect = (Rectangle){
            .x = x,
            .y = y,
            .width = 16,
            .height = 16,
        },
        .initial_x_position = x,
    };

    return alien;
}

void add_alien(entity_array* arr, int type, float xposition, float yposition) {
    if (arr->size >= arr->cap) {
        printf("Error: array full\n");
        return;
    }
    arr->data[arr->size] = CreateAlien(type, xposition, yposition);
    arr->size++;

}

void add_projectile(entity_array* arr, Entity* player) {
    if (arr->size >= arr->cap) {
        printf("Error: array full\n");
        return;
    }

    Entity projectile = (Entity){
        .vertical_direction = player->vertical_direction,
        .horizontal_direction = player->horizontal_direction,
        .current_direction = player->current_direction,
        .textures = player->textures,    
        .current_texture = LoadTexture("assets/pixelart/projectile.png"),
        .hp = 1.0f,
        .i_time = 0.0f,
        .type = PROJECTILE,
        .dest_rect = (Rectangle){
            .x = player->dest_rect.x + 4,
            .y = player->dest_rect.y + 4,
            .width = 8,
            .height = 8,
        },
    }; 

    arr->data[arr->size] = projectile;
    arr->size++;
}


void move_projectile(Entity* proj) {
    switch (proj->current_direction) {
    case UP:
        proj->dest_rect.y += -PROJECTILE_SPEED * GetFrameTime();
        break;

    case LEFT:
        proj->dest_rect.x += -PROJECTILE_SPEED * GetFrameTime();
        break;

    case DOWN:
        proj->dest_rect.y += PROJECTILE_SPEED * GetFrameTime();
        break;

    case RIGHT:
        proj->dest_rect.x += PROJECTILE_SPEED * GetFrameTime();
        break;
    default:
        printf("Error: projectile current direction value not valid\n");
        proj->dest_rect.y += -PROJECTILE_SPEED * GetFrameTime();
        break;
    }

}



Entity initialize_melee() {
    Textures melee_textures = (Textures){
    .texture_up = LoadTexture("assets/pixelart/melee_up.png"),
    .texture_down = LoadTexture("assets/pixelart/melee_down.png"),
    .texture_side = LoadTexture("assets/pixelart/melee_side.png"),
    };

    Entity melee = (Entity){
        .vertical_direction = 1,
        .horizontal_direction = 1,
        .current_direction = UP,
        .textures = melee_textures,    
        .current_texture = melee_textures.texture_side,
        .hp = 0.0f,
        .i_time = 0.0f,
        .type = MELEE,
        .dest_rect = (Rectangle){
            .x = 0,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };
    return melee;
}

void spawn_melee(Entity* melee, Entity* player) {
    melee->hp = LIFE_TIME_MELEE;
    melee->vertical_direction = player->vertical_direction;
    melee->horizontal_direction = player->horizontal_direction;
    melee->current_direction = player->current_direction;

    switch (melee->current_direction) {
    case UP:
        melee->dest_rect.x = player->dest_rect.x; 
        melee->dest_rect.y = player->dest_rect.y - 16;
        melee->current_texture = melee->textures.texture_up; 
        break;

    case LEFT:
        melee->dest_rect.x = player->dest_rect.x -16; 
        melee->dest_rect.y = player->dest_rect.y;  
        melee->current_texture = melee->textures.texture_side;
        break;

    case DOWN:
        melee->dest_rect.x = player->dest_rect.x; 
        melee->dest_rect.y = player->dest_rect.y + 16; 
        melee->current_texture = melee->textures.texture_down;
        break;

    case RIGHT:
        melee->dest_rect.x = player->dest_rect.x + 16; 
        melee->dest_rect.y = player->dest_rect.y; 
        melee->current_texture = melee->textures.texture_side;
        break;

    default:
        printf("Error: melee current direction value not valid\n");
        break;
    }
}

void colision_projectile_alien(Entity* alien, entity_array* proj_array) {
    for (int i = 0; i < proj_array->size; i++) {

        if (CheckCollisionRecs(alien->dest_rect, proj_array->data[i].dest_rect)
            && alien->hp > 0) {

            alien->hp -= 2;
            alien->i_time = MAX_I_TIME;

            proj_array->size--;

            for (int j = i; j < proj_array->size; j++) {
                proj_array->data[j] = proj_array->data[j + 1];
            }

            i--;
        }
    }
}

void colision_melee_alien(Entity* alien, Entity* melee) {
    if (CheckCollisionRecs(alien->dest_rect, melee->dest_rect) && alien->hp) {
        alien->hp -= 4;
        alien->i_time = MAX_I_TIME;
    }
}
void move_alien_patrol(Entity* alien) {
    const float speed = 20.0f;
    float delta = speed * GetFrameTime();

    float minX = alien->initial_x_position;
    float maxX = alien->initial_x_position + PATROL_LIMIT;

    if (alien->horizontal_direction == 1) {
        alien->dest_rect.x += delta;
        if (alien->dest_rect.x >= maxX) {
            alien->dest_rect.x = maxX;
            alien->horizontal_direction = -1;
        }
    }
    else {
        alien->dest_rect.x -= delta;
        if (alien->dest_rect.x <= minX) {
            alien->dest_rect.x = minX;
            alien->horizontal_direction = 1;
        }
    }
}
