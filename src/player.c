#include <raylib.h>
#include <entities.h>
// --- PIXEL ART ENGINE CONFIGURATION ---
#define GAME_WIDTH 160
#define GAME_HEIGHT 144
#define PIXEL_SCALE 5 // The fixed multiplier for rendering (e.g., 5X scale)
// --------------------------------------
//move_player changes player position, direction and current texture
void move_player(Entity* player, Camera2D* camera) {
    if (IsKeyDown(KEY_W)){
        player->dest_rect.y += -10 * GetFrameTime();
        player->current_texture = player->textures.texture_up;
	camera->target.y += -10 * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)){
        player->dest_rect.x += -10* GetFrameTime();
        player->current_texture = player->textures.texture_side;
        player->direction = 1;
	camera->target.x += -10 * GetFrameTime();

    }
    if (IsKeyDown(KEY_S)){
        player->dest_rect.y += 10 * GetFrameTime();
        player->current_texture = player->textures.texture_down;
	camera->target.y += 10 * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)){
        player->dest_rect.x += 10 * GetFrameTime();
        player->current_texture = player->textures.texture_side;
        player->direction = -1;
	camera->target.x += 10 * GetFrameTime();
    }
}
//move_player changes alien position, direction and current texture
void move_alien(Entity* alien) {
    if (IsKeyDown(KEY_UP)){
        alien->dest_rect.y += -10 *  GetFrameTime();
        alien->current_texture = alien->textures.texture_up;
    }
    if (IsKeyDown(KEY_LEFT)){
        alien->dest_rect.x += -10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->direction = 1;
    }
    if (IsKeyDown(KEY_DOWN)){
        alien->dest_rect.y += 10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_down;
    }
    if (IsKeyDown(KEY_RIGHT)){
        alien->dest_rect.x += 10 * GetFrameTime();
        alien->current_texture = alien->textures.texture_side;
        alien->direction = -1;
    }
}


//Initializing main
int main(void) {

	const int screenWidth = GAME_WIDTH * PIXEL_SCALE;
    const int screenHeight = GAME_HEIGHT * PIXEL_SCALE;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
	
	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);	//la pantalla virtual de baja resolución
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);    // para evitar que se vea borroso
    
    
    Camera2D camera = {0};
    camera.target = (Vector2){0.0f, 0.0f};
    camera.offset = (Vector2){0.0f, 0.0f};
    camera.zoom = 1.0f;

    //Loading player textures
    Texture2D player_up = LoadTexture("assets/pixelart/t_up_0.png");
    Texture2D player_down = LoadTexture("assets/pixelart/t_down_0.png");
    Texture2D player_side = LoadTexture("assets/pixelart/t_side_0.png");
    
    //Loading alien textures
    Texture2D alien_up = LoadTexture("assets/pixelart/alien_up.png");
    Texture2D alien_side = LoadTexture("assets/pixelart/alien_side_0.png");
    Texture2D alien_down = LoadTexture("assets/pixelart/alien_down.png");

    //Initializing player 
    Textures player_textures = (Textures) {
    .texture_up = player_up,
    .texture_down = player_down,
    .texture_side = player_side,
    };
    Entity player = (Entity) {
        .direction = 1,
        .textures = player_textures,
        .current_texture = player.textures.texture_down,
        .hp = 100,
        .dest_rect = (Rectangle){
        .x = 10,
        .y = 20,
        .width = 16,
        .height = 16,
        }
    };

    //Initializing alien
    Textures alien_textures = (Textures) {
    .texture_up = alien_up,
    .texture_down = alien_down,
    .texture_side = alien_side,
    };
    Entity alien  = (Entity) {
        .direction = 1,
        .textures = alien_textures,
        .current_texture = alien.textures.texture_down,
        .hp = 100,
        .dest_rect = (Rectangle){
        .x = 40,
        .y = 20,
        .width = 16,
        .height = 16,
        }
    };


    //Opening window
    while(!WindowShouldClose()) {
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
	    BeginMode2D(camera);
            if (player.hp > 0) {
                move_player(&player, &camera);
                DrawTexturePro(player.current_texture, (Rectangle){0, 0, player.direction * 16, 16}, player.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}

            if (alien.hp > 0) {
                move_alien(&alien);
                DrawTexturePro(alien.current_texture, (Rectangle){0, 0, alien.direction * 16, 16}, alien.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}
	    EndMode2D();
        EndTextureMode();
        
        BeginDrawing();
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

    UnloadTexture(player_up);
    UnloadTexture(player_down);
    UnloadTexture(player_side);
    UnloadTexture(alien_up);
    UnloadTexture(alien_down);
    UnloadTexture(alien_side);
    CloseWindow();
    return 0;
}
