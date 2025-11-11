#include <raylib.h>
//The textures struct will be included inside the Sprite struct
typedef struct textures {
    Texture2D texture_up;
    Texture2D texture_down;
    Texture2D texture_side;
} textures;

//Sprite contains all player info
typedef struct Sprite {
    float direction;
    struct textures textures;
    Texture2D current_texture; //Says what texture will be drawn
    Rectangle dest_rect;
} Sprite;

//move_player changes player position, direction and current texture
void move_player(Sprite* player) {
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

//Initializing main
int main(void) {

    InitWindow(600, 400, "Main window");
    SetTargetFPS(30);
    //Loading player textures
    Texture2D player_up = LoadTexture("assets/pixelart/t_up_0.png");
    Texture2D player_down = LoadTexture("assets/pixelart/t_down_0.png");
    Texture2D player_side = LoadTexture("assets/pixelart/t_side_0.png");
    
    //Initializing player 
    textures player_textures = (textures) {
    .texture_up = player_up,
    .texture_down = player_down,
    .texture_side = player_side,
    };
    Sprite player = (Sprite) {
        .direction = 1,
        .textures = player_textures,
        .current_texture = player.textures.texture_down,
        .dest_rect = (Rectangle){
        .x = 100,
        .y = 200,
        .width = 80,
        .height = 80,
        }
    };
    //Opening window
    while(!WindowShouldClose()) {
        move_player(&player);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(player.current_texture, (Rectangle){0, 0, player.direction * 16, 16}, player.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE );
        EndDrawing();
    };

    UnloadTexture(player_up);
    UnloadTexture(player_down);
    UnloadTexture(player_side);
    CloseWindow();
    return 0;
}
