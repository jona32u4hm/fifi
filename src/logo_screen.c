#include "logo_screen.h"
#include "raylib.h"
// logo_screen.c
void UpdateLogoScreen(float *timer, float *alpha, GameState *currentState) {
    // Define the state timings
    #define FADE_IN_TIME 2.0f
    #define FULL_VIEW_TIME 2.0f
    #define FADE_OUT_TIME 2.0f

    *timer += GetFrameTime();

    if (*timer < FADE_IN_TIME) {
        *alpha = *timer / FADE_IN_TIME;
    } else if (*timer < FADE_IN_TIME + FULL_VIEW_TIME) {
        *alpha = 1.0f;
    } else if (*timer < FADE_IN_TIME + FULL_VIEW_TIME + FADE_OUT_TIME) {
        float fadeOutElapsed = *timer - (FADE_IN_TIME + FULL_VIEW_TIME);
        *alpha = 1.0f - (fadeOutElapsed / FADE_OUT_TIME);
    } else {
        // Transition
        *currentState = SPLASH;
        *timer = 0.0f;
    }

    // Drawing logic would be in a separate DrawLogoScreen function
}
