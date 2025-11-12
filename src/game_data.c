#include "level_data.h"









static LevelData allLevels[] = {
    // Level ID 1 (Index 0)
    {
        .mapWidth = 32, 
        .mapHeigth = 32, 
        .tileMapData = NULL,
        .enemyCount = 5,
        .enemies = NULL,
        .playerStart = {.startPos = {50, 50}}
        
    },
    // Level ID 2 (Index 1)
    {
        .mapWidth = 32, 
        .mapHeigth = 32, 
        .tileMapData = NULL,
        .enemyCount = 5,
        .enemies = NULL,
        .playerStart = {.startPos = {50, 50}}
        
    },
    // ...
};
const int TOTAL_LEVELS = sizeof(allLevels) / sizeof(LevelData); // Calculate total number of levels









// Function to fetch the level data based on the ID
LevelData GetLevelData(int levelID) {
    if (levelID > 0 && levelID <= TOTAL_LEVELS) {
        // Arrays are 0-indexed, so Level 1 is at index 0
        return allLevels[levelID - 1]; 
    }
    // default empty level data structure
    return (LevelData){0}; 
}
