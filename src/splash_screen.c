#include "splash_screen.h"
#include "raylib.h"
// splash_screen.c



void UpdateSplashScreen(float *timer, float *alpha, GameState *currentState, Texture2D *splashTexture, SplashState *splashState) {
    // Define state timings
    #define splash_FADE_IN_TIME 2.0f
    #define splash_FADE_OUT_TIME 2.0f

    *timer += GetFrameTime();
    
    if (splashTexture->id == 0){//load si no lo ha hecho
        *splashTexture = LoadTexture("assets/pixelart/title.png");
        SetTextureFilter(*splashTexture, TEXTURE_FILTER_POINT);
        return; 
    }
    switch (*splashState){
    	case FADEIN:
    		if (*timer < splash_FADE_IN_TIME) {
				*alpha = *timer / splash_FADE_IN_TIME;
			} else *splashState = WAIT;
    		break;
    	case WAIT:
    		if (IsKeyPressed(KEY_ENTER)){
		    	*timer = 0.0f; 
		    	*splashState = FADEOUT;
		    }else *alpha = 1.0f;
    		break;
    	case FADEOUT:
    		if (*timer < splash_FADE_OUT_TIME) {
				*alpha = (splash_FADE_IN_TIME - *timer) / splash_FADE_IN_TIME;
			} else {
				*splashState = FADEIN; //para la próxima
				*currentState = LOADING;
				*timer = 0.0f;
		   		UnloadTexture(*splashTexture);
				splashTexture->id = 0; // Important to reset ID
			} 
    		break;
    }
    

    return;

    // Drawing logic outside
}
