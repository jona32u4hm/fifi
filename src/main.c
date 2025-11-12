/* archivo principal del proyecto. 
    contiene:
        - setup y parámetros 
        - game state machine
        - main loop 
*/

#include "raylib.h"
#include <stdio.h>



#include "game_data.h"
#include "logo_screen.h"
#include "splash_screen.h"

// --- PIXEL ART ENGINE CONFIGURATION ---
#define GAME_WIDTH 160
#define GAME_HEIGHT 144
#define PIXEL_SCALE 5 // The fixed multiplier for rendering (e.g., 5X scale)
// --------------------------------------

// --- Textures --- 
Texture2D logoTexture;
Texture2D splashTexture;
//----------------



int main(void){
	const int screenWidth = GAME_WIDTH * PIXEL_SCALE;
    const int screenHeight = GAME_HEIGHT * PIXEL_SCALE;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
	
	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);	//la pantalla virtual de baja resolución
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);    // para evitar que se vea borroso
    
    
    GameState currentState = LOGO; //game_data.h
    SplashState splashState = FADEIN; //splash_screen.h
    float timer = 0.0; 
    float alpha = 0.0f; // Initialize alpha to fully transparent (0.0)
    int alphaByte; // for fade in/out effect
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
            case PLAYING:
                break;
            case PAUSED:
                break;
            case GAMEOVER:
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
    if (logoTexture.id != 0){
		UnloadTexture(logoTexture);
	}
    if (splashTexture.id != 0){
		UnloadTexture(splashTexture);
	}
	UnloadRenderTexture(target);
	UnloadFont(GetFontDefault());
    CloseWindow();
    return 0; 
}
