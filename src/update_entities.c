#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "entities.h"
#include "player.h"
#include "colisions.h"
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



void update_entities(Camera2D* camera, Entity* player, entity_array* aliens_array, Entity* melee, entity_array* proj_array, float* cooldown_proj, float* cooldown_melee, LevelData* currentLevel) {
    
    //Varaibles for colissions with walls
    float oldX = player->dest_rect.x;
	float oldY = player->dest_rect.y;



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

    //Colisions for player with walls
    if (CheckPlayerCollision(currentLevel, player)) {
        player->dest_rect.x=oldX;
        player->dest_rect.y=oldY;
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
        DrawTexturePro((proj_array->data + i)->current_texture, (Rectangle){0, 0, (proj_array->data + i)->horizontal_direction * 8, 8}, (proj_array->data + i)->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
        move_projectile(proj_array->data + i);
    }
    
    float oldAX;
    float oldAY;
    for (int i = 0; i < aliens_array->size; i++) {
        if ((aliens_array->data + i)->hp <= 0) {
            continue;
        }

    	oldAX = (aliens_array->data + i)->dest_rect.x;
        oldAY = (aliens_array->data + i)->dest_rect.y; 

        //Checking if a projectile or melee touches an enemy while not in inmunity time
        if ((aliens_array->data + i)->i_time <=0) { 
            colision_projectile_alien(aliens_array->data + i, proj_array);
        }
        if ((aliens_array->data + i)->i_time <=0 && melee->hp > 0) {
            colision_melee_alien(aliens_array->data + i, melee);
        }
        //Drawing alien
        if ((aliens_array->data + i)->hp > 0) {
            switch ((aliens_array->data + i)->type) {
                case ALIEN_PATROL:
                    move_alien_patrol(aliens_array->data + i);
                    DrawTexturePro((aliens_array->data + i)->current_texture, (Rectangle){0, 0, (aliens_array->data + i)->horizontal_direction * 16, 16}, (aliens_array->data + i)->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
                    break;
                case ALIEN_GUARD: 
                    move_alien_guard(aliens_array->data + i, player, currentLevel);
                    DrawTexturePro((aliens_array->data + i)->current_texture, (Rectangle){0, 0, (aliens_array->data + i)->horizontal_direction * 16, 16}, (aliens_array->data + i)->dest_rect, (Vector2){0, 0}, 0.0, BLUE);

                    break;
            }
        }
        (aliens_array->data + i)->i_time -= GetFrameTime();
        //Colisions enemy with walls
        if (CheckEntityCollision(currentLevel, aliens_array->data + i)){
            (aliens_array->data + i)->dest_rect.x=oldAX;
            (aliens_array->data + i)->dest_rect.y=oldAY;
        }
        if (CheckCollisionRecs(player->dest_rect, (aliens_array->data + i)->dest_rect) && player->i_time <= 0) {
            player->hp -= ALIEN_DAMAGE;
            player->i_time = MAX_I_TIME;
        }
    }
        player->i_time -= GetFrameTime();

}

