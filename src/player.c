
#include "player.h"
#include <raylib.h>
#include <entities.h>
#include <math.h>
#include "game_data.h"
#include "colision_wall.h"
#define PLAYER_SPEED 40

//move_player changes player position, direction and current texture
void move_player(Entity* player, Camera2D* camera) {
    if (IsKeyDown(KEY_W)){
        player->dest_rect.y += -PLAYER_SPEED * GetFrameTime();
        player->current_texture = player->textures.texture_up;
	    camera->target.y += -PLAYER_SPEED * GetFrameTime();
	    player->vertical_direction = 1;
	    player->current_direction = UP;
    }
    if (IsKeyDown(KEY_A)){
        player->dest_rect.x += -PLAYER_SPEED* GetFrameTime();
        player->current_texture = player->textures.texture_side;
	    camera->target.x += -PLAYER_SPEED * GetFrameTime();
	    player->horizontal_direction = 1;
	    player->current_direction = LEFT;
    }
    if (IsKeyDown(KEY_S)){
        player->dest_rect.y += PLAYER_SPEED * GetFrameTime();
        player->current_texture = player->textures.texture_down;
	    camera->target.y += PLAYER_SPEED * GetFrameTime();
	    player->vertical_direction = -1;
	    player->current_direction = DOWN;
    }
    if (IsKeyDown(KEY_D)){
        player->dest_rect.x += PLAYER_SPEED * GetFrameTime();
        player->current_texture = player->textures.texture_side;
	    camera->target.x += PLAYER_SPEED * GetFrameTime();
	    player->horizontal_direction = -1;
	    player->current_direction = RIGHT;
    }
}

void move_alien_guard(Entity* alien, Entity* player, LevelData* currentLevel) {
//for future versions, enemy type should be checked before running this routine

	//check player in range?
	unsigned char range = 0; 
	if ( sqrt( pow(player->dest_rect.x - alien->dest_rect.x,2) + pow(player->dest_rect.y - alien->dest_rect.y,2) ) < PLAYER_FOLLOW_RANGE){
	range = 1; 
	alien->state = 2; //follow player
	}
	
	//update alien state machine:
	switch(alien->state){
		case 0:// move right 
		    alien->dest_rect.x += 10 * GetFrameTime();
		    alien->current_texture = alien->textures.texture_side;
		    alien->horizontal_direction = -1;
		    int y0 = (int)(alien->dest_rect.y+8)/16; //had to use this instead of collission check routine. we should check that one, cause it gave me problems
		    int x0 = (int)alien->dest_rect.x/16+1;
  			if (currentLevel->map[y0][x0] != 0){
  				alien->state = 1;
  				alien->dest_rect.x += -10 * GetFrameTime();
  			}
		return;
		case 1://move left
		    alien->dest_rect.x += -10 * GetFrameTime();
		    alien->current_texture = alien->textures.texture_side;
		    alien->horizontal_direction = 1;
		    int y1 = (int)(alien->dest_rect.y+8)/16;
		    int x1 = (int)alien->dest_rect.x/16;
  			if (currentLevel->map[y1][x1] != 0){
  				alien->state = 0;
  				alien->dest_rect.x += 10 * GetFrameTime();
  			}
		return;
		case 2: //follow player	
			if (range == 0) {
				alien->state = 0;
				return;
			}
			
			int x2 = (int)(alien->dest_rect.x+8)/16; 
		    int y2 = (int)alien->dest_rect.y/16;
			if (player->dest_rect.y < alien->dest_rect.y && currentLevel->map[y2][x2] == 0){ // check player in that direction and also check no collission!
				alien->dest_rect.y += -10 *  GetFrameTime();
				alien->current_texture = alien->textures.texture_up;
				alien->vertical_direction = 1;
			}
			y2 = (int)(alien->dest_rect.y+8)/16; 
		    x2 = (int)alien->dest_rect.x/16;
			if (player->dest_rect.x < alien->dest_rect.x && currentLevel->map[y2][x2] == 0){
				alien->dest_rect.x += -10 * GetFrameTime();
				alien->current_texture = alien->textures.texture_side;
				alien->horizontal_direction = 1;
			}
			x2 = (int)(alien->dest_rect.x+8)/16; 
		    y2 = (int)alien->dest_rect.y/16+1;
			if (player->dest_rect.y > alien->dest_rect.y && currentLevel->map[y2][x2] == 0){
				alien->dest_rect.y += 10 * GetFrameTime();
				alien->current_texture = alien->textures.texture_down;
				alien->vertical_direction = -1;
			}
			y2 = (int)(alien->dest_rect.y+8)/16; 
		    x2 = (int)alien->dest_rect.x/16+1;
			if (player->dest_rect.x > alien->dest_rect.x && currentLevel->map[y2][x2] == 0){
				alien->dest_rect.x += 10 * GetFrameTime();
				alien->current_texture = alien->textures.texture_side;
				alien->horizontal_direction = -1;
			}
		return;
	}
	alien->state = 0;
}




Entity initialize_player() {
    // Loading player textures
    Texture2D player_up   = LoadTexture("assets/pixelart/t_up_0.png");
    Texture2D player_down = LoadTexture("assets/pixelart/t_down_0.png");
    Texture2D player_side = LoadTexture("assets/pixelart/t_side_0.png");

    // Create texture container
    Textures player_textures = (Textures){
        .texture_up = player_up,
        .texture_down = player_down,
        .texture_side = player_side,
    };

    // Create player
    Entity player = (Entity){
        .vertical_direction = 1,
        .horizontal_direction = 1,
        .current_direction = 3,
        .textures = player_textures,
        .current_texture = player_textures.texture_down,
        .hp = 10.0f,
        .i_time = 0.0f,
        .type = PLAYER,
        .dest_rect = (Rectangle){
            .x = 50,
            .y = 50,
            .width = 16,
            .height = 16,
        },
    };

    return player;
}


