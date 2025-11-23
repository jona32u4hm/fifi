// splash_screen.h
#include "game_data.h"
#include "raylib.h"

#ifndef SPLASH_SCREEN_H 
#define SPLASH_SCREEN_H

typedef enum {
    FADEIN,
    WAIT,
    FADEOUT
} SplashState;

void UpdateSplashScreen(float *timer, float *alpha, GameState *currentState, Texture2D *splashTexture, SplashState *splashState);



#endif 
