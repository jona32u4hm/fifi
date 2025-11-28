/* archivo principal del proyecto. 
    contiene:
        - setup y parámetros 
        - game state machine
        - main loop 
*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#include "game_data.h"
#include "logo_screen.h"
#include "splash_screen.h"
#include "colisions.h"
#include "map_render.h"
#include "update_entities.h"
#include "entities.h"
#include "player.h"
#include "colision_wall.h"   // ← necesario para usar CheckPlayerCollision

// --- PIXEL ART ENGINE CONFIGURATION ---
#define GAME_WIDTH 160
#define GAME_HEIGHT 144
#define PIXEL_SCALE 5 // The fixed multiplier for rendering (e.g., 5X scale)
// --------------------------------------

// --- Textures --- 
Texture2D logoTexture;
Texture2D splashTexture;
Texture2D floorTile;
Texture2D wallTile;
//----------------
int currentLevelID = 1;
LevelData *currentLevel;


int main(void){
	
	const int screenWidth = GAME_WIDTH * PIXEL_SCALE;
    const int screenHeight = GAME_HEIGHT * PIXEL_SCALE;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
	
	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);    
    
    
    GameState currentState = LOGO; //game_data.h
    SplashState splashState = FADEIN; //splash_screen.h
    float timer = 0.0; 
    float alpha = 0.0f; // Initialize alpha to fully transparent (0.0)
    int alphaByte; // for fade in/out effect

    //Here goes all update_entities dependencies
    Camera2D camera = initialize_camera();

    Entity player = initialize_player();
    Entity melee = initialize_melee();

    entity_array proj_array = init_ent_array(PROJECTILE_CAP);
    entity_array aliens_array = init_ent_array(ALIENS_CAP);  

    //Adding enemies. For modularity, in future versions this information would be in an external file
    add_alien(&aliens_array, ALIEN_PATROL, 85, 50);
    add_alien(&aliens_array, ALIEN_PATROL, 80, 160);
    add_alien(&aliens_array, ALIEN_PATROL, 80, 400);
    add_alien(&aliens_array, ALIEN_GUARD, 80, 360);
    add_alien(&aliens_array, ALIEN_PATROL, 270, 35);
    add_alien(&aliens_array, ALIEN_GUARD, 300, 84);
    add_alien(&aliens_array, ALIEN_GUARD, 400, 82);
    add_alien(&aliens_array, ALIEN_PATROL, 400, 170);
    add_alien(&aliens_array, ALIEN_GUARD, 440, 274);
    add_alien(&aliens_array, ALIEN_GUARD, 400, 400);
    add_alien(&aliens_array, ALIEN_GUARD, 200, 450);

    float cooldown_proj = MIN_TIME_PROJ;
    float cooldown_melee = MIN_TIME_MELEE;
	logoTexture = LoadTexture("assets/pixelart/logo.png");
    Texture2D gameOver = LoadTexture("assets/pixelart/GameOver.png");
	SetTextureFilter(logoTexture, TEXTURE_FILTER_POINT);
    
    if (proj_array.data == NULL || aliens_array.data ==  NULL) {
        printf("Memory error");
        currentState = GAMEOVER;
    }
    while (!WindowShouldClose()){

	//dibujar sobre pantalla virtual:
        BeginTextureMode(target);
        switch (currentState){
            //main game code
            case LOGO:
                    UpdateLogoScreen(&timer, &alpha, &currentState, &logoTexture);
                    ClearBackground(BLACK);
                    // Create a color with the calculated alpha value (0 to 255)
                    alphaByte = (int)(alpha * 255.0f);
                    Color logoColor = { 255, 255, 255, alphaByte }; // White color with current alpha
                    DrawTexture(logoTexture, 
                                (GAME_WIDTH/2) - (logoTexture.width/2), 
                                (GAME_HEIGHT/2) - (logoTexture.height/2), 
                                logoColor);
                break;
            case SPLASH:
                    UpdateSplashScreen(&timer, &alpha, &currentState, &splashTexture, &splashState);
                    ClearBackground(BLACK);
                    // Create a color with the calculated alpha value (0 to 255)
                    alphaByte = (int)(alpha * 255.0f);
                    Color splashColor = { 255, 255, 255, alphaByte }; // White color with current alpha
                    DrawTexture(splashTexture, 
                                (GAME_WIDTH/2) - (splashTexture.width/2), 
                                (GAME_HEIGHT/2) - (splashTexture.height/2), 
                                splashColor);
                break;
            case LOADING:
            		//copy next level's structure to currentLevel
            		char *filename = GetLevelPath(currentLevelID);
    				currentLevel = LoadLevelData(filename);
				    if (currentLevel != NULL) {
						printf("Level loaded successfully!\n");
						PrintLevelData(currentLevel);
						currentState = PLAYING;
					} else {
						printf("Failed to load level data.\n");
						currentState = SPLASH;
					}
					
				    if (floorTile.id == 0){//load si no lo ha hecho
						floorTile = LoadTexture("assets/pixelart/floor.png");
						SetTextureFilter(floorTile, TEXTURE_FILTER_POINT);
					}
					if (wallTile.id == 0){//load si no lo ha hecho
						wallTile = LoadTexture("assets/pixelart/wall1.png");
						SetTextureFilter(wallTile, TEXTURE_FILTER_POINT);
					}   


                break;
            case PLAYING:
			{
            
                    BeginMode2D(camera);

                    ClearBackground(BLACK);
                    renderMap(currentLevel, floorTile, wallTile);
                    update_entities(&camera, &player, &aliens_array, &melee, &proj_array,
                                    &cooldown_proj, &cooldown_melee, currentLevel);

                    EndMode2D();

                    DrawText("HP:", 5, 5, 10, BLACK);

                    for (int i = 0; i < player.hp; i++) {
                        DrawRectangle(40 + 12 * i, 5, 10, 10, RED);
                    }

                    camera.offset = (Vector2){ GAME_WIDTH/2, GAME_HEIGHT/2 };
                    camera.target = (Vector2){
                        player.dest_rect.x + player.dest_rect.width/2,
                        player.dest_rect.y + player.dest_rect.height/2
                    };

                    if (player.hp <= 0) {
                        currentState = GAMEOVER;
                    }

			}
                break;
            case PAUSED:
                break;
            case GAMEOVER:
                    DrawTexture(gameOver,
                    (GAME_WIDTH/2) - (logoTexture.width/2),
                    (GAME_HEIGHT/2) - (logoTexture.height/2),
                    RAYWHITE);
                break;
        }
        EndTextureMode();
        //--------------------------------------pixel art drawing---------------------------
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
    }
    
    
    
    ////////////////////////////////////////CLEANUP///////////////////////////////////////
	if (currentLevel != NULL) {
		FreeLevelData(currentLevel);
		printf("level freed...\n");
	} else printf("NULL level pointer???\n");
    
    if (floorTile.id != 0){
		UnloadTexture(logoTexture);
	}
    if (wallTile.id != 0){
		UnloadTexture(splashTexture);
	} 
    if (logoTexture.id != 0){
		UnloadTexture(logoTexture);
	}
    if (splashTexture.id != 0){
		UnloadTexture(splashTexture);
	}
	UnloadRenderTexture(target);
	UnloadFont(GetFontDefault());
    CloseWindow();

    // Unload player textures
    UnloadTexture(player.textures.texture_up);
    UnloadTexture(player.textures.texture_down);
    UnloadTexture(player.textures.texture_side);

    // Unload alien textures
    for (int i = 0; i < aliens_array.size; i++) {
        UnloadTexture((aliens_array.data + i)->textures.texture_up);
        UnloadTexture((aliens_array.data + i)->textures.texture_down);
        UnloadTexture((aliens_array.data + i)->textures.texture_side);
    }

    for (int i = 0; i < proj_array.size; i++) {
        UnloadTexture((proj_array.data + i)->current_texture);
    }
    UnloadTexture(melee.textures.texture_up);
    UnloadTexture(melee.textures.texture_down);
    UnloadTexture(melee.textures.texture_side);
    free(proj_array.data);

    UnloadTexture(gameOver);
    return 0; 
}


