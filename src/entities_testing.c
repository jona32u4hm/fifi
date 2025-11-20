#include <raylib.h>
#include "entities.h"
#include "player.h"
// --- PIXEL ART ENGINE CONFIGURATION ---
#define GAME_WIDTH 160
#define GAME_HEIGHT 144
#define PIXEL_SCALE 5 // The fixed multiplier for rendering (e.g., 5X scale)
// --------------------------------------
//move_player changes player position, direction and current texture
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
    
    Entity player = initialize_player();
    Entity alien = CreateAlien();


    //Opening window
    while(!WindowShouldClose()) {
        BeginTextureMode(target); // se empieza a dibujar sobre la pantalla virtual "target"
            ClearBackground(RAYWHITE);
	    BeginMode2D(camera);
            if (player.hp > 0) {
                move_player(&player, &camera);
                DrawTexturePro(player.current_texture, (Rectangle){0, 0, player.horizontal_direction * 16, 16}, player.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}

            if (alien.hp > 0) {
                move_alien(&alien);
                DrawTexturePro(alien.current_texture, (Rectangle){0, 0, alien.horizontal_direction * 16, 16}, alien.dest_rect, (Vector2){0, 0}, 0.0, RAYWHITE);
}
	    EndMode2D();
        EndTextureMode();
        
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

    return 0;
}
