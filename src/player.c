#include <raylib.h>
//The textures struct will be included inside the entity struct
typedef struct textures {
    Texture2D texture_up;
    Texture2D texture_down;
    Texture2D texture_side;
} textures;

//entity contains all player info
typedef struct entity {
    float direction;
    struct textures textures;
    Texture2D current_texture; //Says what texture will be drawn
    Rectangle dest_rect;
    float hp;
} entity; 
//move_player changes player position, direction and current texture
void move_player(entity* player) {
    if (IsKeyDown(KEY_W)){
        player->dest_rect.y += -100 * GetFrameTime();
        player->current_texture = player->textures.texture_up;
    }
    if (IsKeyDown(KEY_A)){
        player->dest_rect.x += -100 * GetFrameTime();
        player->current_texture = player->textures.texture_side;
        player->direction = 1;
    }
    if (IsKeyDown(KEY_S)){
        player->dest_rect.y += 100 * GetFrameTime();
        player->current_texture = player->textures.texture_down;
    }
    if (IsKeyDown(KEY_D)){
        player->dest_rect.x += 100 * GetFrameTime();
        player->current_texture = player->textures.texture_side;
        player->direction = -1;
    }
}
//move_player changes alien position, direction and current texture
void move_alien(entity* alien) {
    if (IsKeyDown(KEY_UP)){
        alien->dest_rect.y += -100 * GetFrameTime();
        alien->current_texture = alien->textures.texture_up;
    }
    if (IsKeyDown(KEY_LEFT)){
        alien->dest_rect.x += -100 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->direction = 1;
    }
    if (IsKeyDown(KEY_DOWN)){
        alien->dest_rect.y += 100 * GetFrameTime();
        alien->current_texture = alien->textures.texture_down;
    }
    if (IsKeyDown(KEY_RIGHT)){
        alien->dest_rect.x += 100 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->direction = -1;
    }
}


//Initializing main
int main(void) {

    InitWindow(600, 400, "Main window");
    SetTargetFPS(30);
    //Loading player textures
    Texture2D player_up = LoadTexture("assets/pixelart/t_up_0.png");
    Texture2D player_down = LoadTexture("assets/pixelart/t_down_0.png");
    Texture2D player_side = LoadTexture("assets/pixelart/t_side_0.png");
    
    //Loading alien textures
    Texture2D alien_up = LoadTexture("assets/pixelart/alien_up.png");
    Texture2D alien_side = LoadTexture("assets/pixelart/alien_side_0.png");
    Texture2D alien_down = LoadTexture("assets/pixelart/alien_down.png");

    //Initializing player 
    textures player_textures = (textures) {
    .texture_up = player_up,
    .texture_down = player_down,
    .texture_side = player_side,
    };
    entity player = (entity) {
        .direction = 1,
        .textures = player_textures,
        .current_texture = player.textures.texture_down,
        .hp = 100,
        .dest_rect = (Rectangle){
        .x = 100,
        .y = 200,
        .width = 80,
        .height = 80,
        }
    };

    //Initializing alien
    textures alien_textures = (textures) {
    .texture_up = alien_up,
    .texture_down = alien_down,
    .texture_side = alien_side,
    };
    entity alien  = (entity) {
        .direction = 1,
        .textures = alien_textures,
        .current_texture = alien.textures.texture_down,
        .hp = 100,
        .dest_rect = (Rectangle){
        .x = 400,
        .y = 200,
        .width = 80,
        .height = 80,
        }
    };


    //Opening window
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (player.hp > 0) {
                move_player(&player);
                DrawTexturePro(player.current_texture, (Rectangle){0, 0, player.direction * 16, 16}, player.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}

            if (alien.hp > 0) {
                move_alien(&alien);
                DrawTexturePro(alien.current_texture, (Rectangle){0, 0, alien.direction * 16, 16}, alien.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}

        EndDrawing();
    };

    UnloadTexture(player_up);
    UnloadTexture(player_down);
    UnloadTexture(player_side);
    UnloadTexture(alien_up);
    UnloadTexture(alien_down);
    UnloadTexture(alien_side);
    CloseWindow();
    return 0;
}
