/* archivo principal del proyecto. 
    contiene:
        - setup y parámetros 
        - game state machine
        - main loop 
*/

#include "raylib.h"




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

    while (!WindowShouldClose()){
        BeginDrawing();
        switch (currentState){
            //Código principal del juego
            case LOGO:
                break;
            case SPLASH:
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
