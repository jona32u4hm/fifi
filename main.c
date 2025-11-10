/* archivo principal del proyecto. 
    contiene:
        - setup y parámetros 
        - game state machine
        - main loop 
*/

#include "raylib.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
   
    InitWindow(screenWidth, screenHeight, "FINDING FIFI");
    SetTargetFPS(30);
    

    while (!WindowShouldClose()){
        BeginDrawing();
        {
            //Código principal del juego
        }
        EndDrawing();
    }

    CloseWindow();
    return 0; 
}
