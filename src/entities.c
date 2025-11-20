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
};

void add_projectile(entity_array* arr, Entity* player) {
    if (arr->size >= arr->cap) {
        printf("Error: array full\n");
        return;
    }

    Entity projectile = (Entity){
        .vertical_direction = player->vertical_direction,
        .horizontal_direction = player->horizontal_direction,
        .current_direction = player->current_direction,
        .textures = player->textures,    // OK, copiás todas las texturas
        .current_texture = LoadTexture("assets/pixelart/projectile.png"),
        .hp = 9999,
        .dest_rect = (Rectangle){
            .x = player->dest_rect.x + 4,
            .y = player->dest_rect.y + 4,
            .width = 8,
            .height = 8,
        },
    }; // <-- ESTE PUNTO Y COMA ES OBLIGATORIO

    arr->data[arr->size] = projectile;
    arr->size++;
}

