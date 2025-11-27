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
//move_player changes player position, direction and current texture
//Initializing main

Camera2D initialize_camera() {
    Camera2D camera = {0};
        camera.target = (Vector2){0.0f, 0.0f};
        camera.offset = (Vector2){0.0f, 0.0f};
        camera.zoom = 1.0f;
        return camera;
}



void update_entities(Camera2D* camera, Entity* player, Entity* alien, Entity* wuwa_the_alien, Entity* melee, entity_array* proj_array, float* cooldown_proj, float* cooldown_melee, LevelData* currentLevel) {

        if (*cooldown_proj < MIN_TIME_PROJ) {
            *cooldown_proj += GetFrameTime();
        }

        if ((*(player)).hp > 0.0f) {
            if  (melee->hp <= 0.0f) {
                move_player(player, camera);
            }
            DrawTexturePro(player->current_texture, (Rectangle){0, 0, player->horizontal_direction * 16, 16}, player->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
        }
        if (IsKeyDown(KEY_E) && *cooldown_proj >= MIN_TIME_PROJ) {
            add_projectile(proj_array, player);
            *cooldown_proj = 0.0f;
        }

        if (IsKeyDown(KEY_Q) && melee->hp <= 0.0f && *cooldown_melee >= MIN_TIME_MELEE) {
            spawn_melee(melee, player);
        }
        if (melee->hp > 0.0f) {
            DrawTexturePro(melee->current_texture, (Rectangle){0, 0, melee->horizontal_direction * 16, 16}, melee->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
            melee->hp -= GetFrameTime();
            if (melee->hp <= 0.0f) {
                *cooldown_melee = 0.0f;
            }
        }       

        if  (*cooldown_melee <= MIN_TIME_MELEE && melee->hp <= 0) {
            *cooldown_melee += GetFrameTime();
        }


        for (int i = 0; i < proj_array->size; i++) {
            DrawTexturePro((*(proj_array->data + i)).current_texture, (Rectangle){0, 0, (*(proj_array->data + i)).horizontal_direction * 8, 8}, (*(proj_array->data + i)).dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
            move_projectile(proj_array->data + i);
        }
        if (alien->i_time <=0) { 
            colision_projectile_alien(alien, proj_array);
        }
        if (alien->i_time <=0 && melee->hp > 0) {
            colision_melee_alien(alien, melee);
        }
        if (alien->hp > 0) {
            move_alien(alien);
            DrawTexturePro(alien->current_texture, (Rectangle){0, 0, alien->horizontal_direction * 16, 16}, alien->dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
        }
        alien->i_time -= GetFrameTime();
        
        // it's wuwa the alien's turn!
        if (wuwa_the_alien->i_time <=0) { 
            colision_projectile_alien(wuwa_the_alien, proj_array);
        }
        if (wuwa_the_alien->i_time <=0 && melee->hp > 0) {
            colision_melee_alien(wuwa_the_alien, melee);
        }
        if (wuwa_the_alien->hp > 0) {
			//wuwa's routine
            DrawTexturePro(wuwa_the_alien->current_texture, (Rectangle){0, 0, wuwa_the_alien->horizontal_direction * 16, 16}, wuwa_the_alien->dest_rect, (Vector2){0, 0}, 0.0, ORANGE);
        }
        wuwa_the_alien->i_time -= GetFrameTime();
}

/*
        BeginDrawing(); //en el drawing se dibuja la pantalla virtual
            ClearBackground(BLACK); 
            
			Rectangle sourceRect = { 
				0.0f, 
				0.0f, 
				(float)target.texture.width, 
				(float)-target.texture.height // FLIP!
			};
			Rectangle destRect = { 
				0.0f, // top-left 
				0.0f, // top-left 
				(float)GAME_WIDTH * PIXEL_SCALE,  
				(float)GAME_HEIGHT * PIXEL_SCALE  
			};
			DrawTexturePro(
				target.texture, 
				sourceRect, 
				destRect, 
				(Vector2){ 0.0f, 0.0f }, // draw from top-left
				0.0f,                    // Rotation
				WHITE                    // Tint
			);
            
        EndDrawing();
    };

    // Unload player textures
    UnloadTexture(player.textures.texture_up);
    UnloadTexture(player.textures.texture_down);
    UnloadTexture(player.textures.texture_side);

    // Unload alien textures
    UnloadTexture(alien.textures.texture_up);
    UnloadTexture(alien.textures.texture_down);
    UnloadTexture(alien.textures.texture_side);
    for (int i = 0; i < proj_array->size; i++) {
        UnloadTexture((*(proj_array->data + i)).current_texture);
    }
    Descargar melee aqui
    free(proj_array.data);
    return 0;
}
*/
