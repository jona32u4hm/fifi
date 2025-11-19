#ifndef GAME_DATA_H
#define GAME_DATA_H
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
    int x, y;
    int type;
} Entity; // Entity placeholder

typedef struct {
	Entity *enemies; // array of enemies
	int enemyCount;
}Batch;

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
