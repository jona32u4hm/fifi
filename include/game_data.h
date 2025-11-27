#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "entities.h"

typedef unsigned char byte;
// The GameState enum definition
typedef enum {
    LOGO,
    SPLASH,
    LOADING,
    PLAYING,
    PAUSED, 
    GAMEOVER
} GameState;

typedef struct {
	Entity *enemies; // array of enemies
	int enemyCount;
}Batch;                               //entites.h already has an entity_array struct

typedef struct {
	

    // MAP DATA
    int mapWidth;           // Width of the map (in tiles)
    int mapHeight;          // Height of the map (in tiles)
    
    byte map[128][128]; // dynamic matrix (of tiles)
    
    // ENEMY DATA
	int batchCount;
	Batch *batch;
    

} LevelData;



char *GetLevelPath(int levelID);

LevelData* LoadLevelData(const char* filename);
void FreeLevelData(LevelData* levelData);
void PrintLevelData(const LevelData* levelData);


#endif // GAME_DATA_H
