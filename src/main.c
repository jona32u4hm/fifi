/* archivo principal del proyecto. 
    contiene:
        - setup y parámetros 
        - game state machine
        - main loop 
*/

#include "raylib.h"
#include <stdio.h>



typedef enum {
    LOGO,
    SPLASH,
    PLAYING,
    PAUSED, 
    GAMEOVER
} GameState;






int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
    
    GameState currentState = LOGO;
    float timer = 0.0; 
    while (!WindowShouldClose()){
        BeginDrawing();
        printf("state: %d", currentState);
        switch (currentState){
            //main game code
            case LOGO:
                        timer += GetFrameTime(); // raylib function to get time since last frame
                        printf("timer: %f", timer);
                        ClearBackground(BLACK);
                        DrawText("RAYLIB LOGO", screenWidth / 2 - MeasureText("RAYLIB LOGO", 20) / 2, screenHeight / 2, 20, WHITE);

                        if (timer > 2.0f) { // Display for 2 seconds
                            currentState = SPLASH;
                            timer = 0.0f; // Reset timer for the next state
                        }
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
