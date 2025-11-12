#ifndef GAME_DATA_H
#define GAME_DATA_H

// The GameState enum definition
typedef enum {
    LOGO,
    SPLASH,
    PLAYING,
    PAUSED, 
    GAMEOVER
} GameState;

typedef struct {
    Vector2 spawnPos;
    int typeID;      // e.g., 1 for Slime, 2 for Bat
} EnemySetup;

typedef struct {
    Vector2 startPos;
} PlayerSetup;

typedef struct {
    // MAP DATA
    int mapWidth;           // Width of the map (in tiles)
    int mapHeight;          // Height of the map (in tiles)
    int *tileMapData;       // Pointer to a 1D array of tile IDs (the map)

    // ENEMY DATA
    int enemyCount;
    EnemySetup *enemies;    // Pointer to an array of EnemySetup structs

    // PLAYER DATA
    PlayerSetup playerStart; 
} LevelData;

#endif // GAME_DATA_H
