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







int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
    
    GameState currentState = LOGO;
    float timer = 0.0; 
    float alpha = 0.0f; // Initialize alpha to fully transparent (0.0)
    while (!WindowShouldClose()){
        BeginDrawing();
        printf("state: %d", currentState);
        switch (currentState){
            //main game code
            case LOGO:
                        UpdateLogoScreen(&timer, &alpha, &currentState);
                        ClearBackground(BLACK);
                        // Create a color with the calculated alpha value (0 to 255)
                        int alphaByte = (int)(alpha * 255.0f);
                        Color logoColor = { 255, 255, 255, alphaByte }; // White color with current alpha

                        DrawText("logo", screenWidth / 2 - MeasureText("logo", 40) / 2, screenHeight / 2, 40, logoColor);
                break;
            case SPLASH:
                        ClearBackground(BLACK);
                        DrawText("----------", screenWidth / 2 - MeasureText("------------", 20) / 2, screenHeight / 2, 20, WHITE);
                break;
            case PLAYING:
                break;
            case PAUSED:
                break;
            case GAMEOVER:
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0; 
}
