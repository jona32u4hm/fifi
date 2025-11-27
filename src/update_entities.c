#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "entities.h"
#include "player.h"
// --- PIXEL ART ENGINE CONFIGURATION ---
#define GAME_WIDTH 160
#define GAME_HEIGHT 144
#define PIXEL_SCALE 5 // The fixed multiplier for rendering (e.g., 5X scale)
// --------------------------------------

Camera2D initialize_camera() {
    Camera2D camera = {0};
        camera.target = (Vector2){0.0f, 0.0f};
        camera.offset = (Vector2){0.0f, 0.0f};
        camera.zoom = 1.0f;
        return camera;
}



void update_entities(Camera2D* camera, Entity* player, Entity* alien, Entity* wuwa_the_alien, Entity* melee, entity_array* proj_array, float* cooldown_proj, float* cooldown_melee, LevelData* currentLevel) {
        //Cooldown should charge over time if not full
        if (*cooldown_proj < MIN_TIME_PROJ) {
            *cooldown_proj += GetFrameTime();
        }
        //Calling player_movement. Player cant move if dead or while using melee
        if ((*(player)).hp > 0.0f) {
            if  (melee->hp <= 0.0f) {
                move_player(player, camera);
                
            }
            DrawTexturePro(player->current_texture, (Rectangle){0, 0, player->horizontal_direction * 16, 16}, player->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
        }
        //If player presses E, can shoot if cooldown is full
        if (IsKeyDown(KEY_E) && *cooldown_proj >= MIN_TIME_PROJ) {
            add_projectile(proj_array, player);
            *cooldown_proj = 0.0f;
        }
        //With Q player can melee if cooldown is full
        if (IsKeyDown(KEY_Q) && melee->hp <= 0.0f && *cooldown_melee >= MIN_TIME_MELEE) {
            spawn_melee(melee, player);
        }
        //Drawing melee
        if (melee->hp > 0.0f) {
            DrawTexturePro(melee->current_texture, (Rectangle){0, 0, melee->horizontal_direction * 16, 16}, melee->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
            melee->hp -= GetFrameTime(); //Melee hp is lowered so that it has limited time
            if (melee->hp <= 0.0f) {
                *cooldown_melee = 0.0f; //Cooldown is depleted
            }
        }       
        //Charging melee cooldown only if player is not currently doing melee
        if  (*cooldown_melee <= MIN_TIME_MELEE && melee->hp <= 0) {
            *cooldown_melee += GetFrameTime();
        }

        //Drawing and moving all projectiles
        for (int i = 0; i < proj_array->size; i++) {
            DrawTexturePro((*(proj_array->data + i)).current_texture, (Rectangle){0, 0, (*(proj_array->data + i)).horizontal_direction * 8, 8}, (*(proj_array->data + i)).dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
            move_projectile(proj_array->data + i);
        }
        //Checking if a projectile or melee touches an enemy while not in inmunity time
        if (alien->i_time <=0) { 
            colision_projectile_alien(alien, proj_array);
        }
        if (alien->i_time <=0 && melee->hp > 0) {
            colision_melee_alien(alien, melee);
        }
        //Drawing alien
        if (alien->hp > 0) {
            move_alien(alien);
            DrawTexturePro(alien->current_texture, (Rectangle){0, 0, alien->horizontal_direction * 16, 16}, alien->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
        }
        alien->i_time -= GetFrameTime();
        
        // Now for wuwa the alien, the other type of alien
        if (wuwa_the_alien->i_time <=0) { 
            colision_projectile_alien(wuwa_the_alien, proj_array);
        }
        if (wuwa_the_alien->i_time <=0 && melee->hp > 0) {
            colision_melee_alien(wuwa_the_alien, melee);
        }
        if (wuwa_the_alien->hp > 0) {
			//wuwa's routine
            DrawTexturePro(wuwa_the_alien->current_texture, (Rectangle){0, 0, wuwa_the_alien->horizontal_direction * 16, 16}, wuwa_the_alien->dest_rect, (Vector2){0, 0}, 0.0, ORANGE);
            move_alien_guard(wuwa_the_alien, player, currentLevel);
        }
        wuwa_the_alien->i_time -= GetFrameTime();
}

