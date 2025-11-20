#include <raylib.h>
#include <entities.h>

//move_player changes player position, direction and current texture
void move_player(Entity* player, Camera2D* camera) {
    if (IsKeyDown(KEY_W)){
        player->dest_rect.y += -10 * GetFrameTime();
        player->current_texture = player->textures.texture_up;
	    camera->target.y += -10 * GetFrameTime();
	    player->vertical_direction = 1;
	    player->current_direction = UP;
    }
    if (IsKeyDown(KEY_A)){
        player->dest_rect.x += -10* GetFrameTime();
        player->current_texture = player->textures.texture_side;
	    camera->target.x += -10 * GetFrameTime();
	    player->horizontal_direction = 1;
	    player->current_direction = LEFT;
    }
    if (IsKeyDown(KEY_S)){
        player->dest_rect.y += 10 * GetFrameTime();
        player->current_texture = player->textures.texture_down;
	    camera->target.y += 10 * GetFrameTime();
	    player->vertical_direction = -1;
	    player->current_direction = DOWN;
    }
    if (IsKeyDown(KEY_D)){
        player->dest_rect.x += 10 * GetFrameTime();
        player->current_texture = player->textures.texture_side;
	    camera->target.x += 10 * GetFrameTime();
	    player->horizontal_direction = -1;
	    player->current_direction = RIGHT;
    }
}
//move_player changes alien position, direction and current texture
void move_alien(Entity* alien) {
    if (IsKeyDown(KEY_UP)){
        alien->dest_rect.y += -10 *  GetFrameTime();
        alien->current_texture = alien->textures.texture_up;
	    alien->vertical_direction = 1;
    }
    if (IsKeyDown(KEY_LEFT)){
        alien->dest_rect.x += -10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->horizontal_direction = 1;
    }
    if (IsKeyDown(KEY_DOWN)){
        alien->dest_rect.y += 10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_down;
	    alien->vertical_direction = -1;
    }
    if (IsKeyDown(KEY_RIGHT)){
        alien->dest_rect.x += 10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->horizontal_direction = -1;
    }
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
        .hp = 100,
        .dest_rect = (Rectangle){
            .x = 10,
            .y = 20,
            .width = 16,
            .height = 16,
        },
    };

    return player;
}

Entity CreateAlien() {
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
        .hp = 100,
        .dest_rect = (Rectangle){
            .x = 40,
            .y = 20,
            .width = 16,
            .height = 16,
        },
    };

    return alien;
}



