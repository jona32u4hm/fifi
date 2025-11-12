#include "logo_screen.h"
#include "raylib.h"
// logo_screen.c




void UpdateLogoScreen(float *timer, float *alpha, GameState *currentState, Texture2D *logoTexture) {
    // Define state timings
    #define logo_FADE_IN_TIME 2.0f
    #define logo_FULL_VIEW_TIME 2.0f
    #define logo_FADE_OUT_TIME 2.0f

    *timer += GetFrameTime();
    
	if (logoTexture->id == 0){//load si no lo ha hecho
        *logoTexture = LoadTexture("assets/pixelart/poyopixel.png");
        SetTextureFilter(*logoTexture, TEXTURE_FILTER_POINT);
        return; 
    }
	
    if (*timer < logo_FADE_IN_TIME) {
        *alpha = *timer / logo_FADE_IN_TIME;
    } else if (*timer < logo_FADE_IN_TIME + logo_FULL_VIEW_TIME) {
        *alpha = 1.0f;
    } else if (*timer < logo_FADE_IN_TIME + logo_FULL_VIEW_TIME + logo_FADE_OUT_TIME) {
        float fadeOutElapsed = *timer - (logo_FADE_IN_TIME + logo_FULL_VIEW_TIME);
        *alpha = 1.0f - (fadeOutElapsed / logo_FADE_OUT_TIME);
    } else {
        // Transition
        *currentState = SPLASH;
        *timer = 0.0f;
   		UnloadTexture(*logoTexture);
    	logoTexture->id = 0; // Important to reset ID

        return;
    }

    // Drawing logic outside
}
