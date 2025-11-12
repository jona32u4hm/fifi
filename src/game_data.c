#include "level_data.h"

static LevelData allLevels[] = {
    // Level ID 1 (Index 0)
    {
        .mapWidth = 64, 
        .mapHeight = 36, 
        .enemyCount = 5,
        // tileMapData and enemies are NULL/zero-initialized by default
        .playerStart = {.startPos = {50, 50}, .startHealth = 100.0f}
        // NOTE: This array doesn't define the map numbers or enemy types yet!
    },
    // Level ID 2 (Index 1)
    {
        .mapWidth = 128, 
        .mapHeight = 72, 
        .enemyCount = 10,
        .playerStart = {.startPos = {100, 100}, .startHealth = 100.0f}
    }
    // ...
};

const int TOTAL_LEVELS = sizeof(allLevels) / sizeof(LevelData); // Calculate total number of levels

// Function to fetch the level data based on the ID
LevelData GetLevelData(int levelID) {
    if (levelID > 0 && levelID <= TOTAL_LEVELS) {
        // Arrays are 0-indexed, so Level 1 is at index 0
        return allLevels[levelID - 1]; 
    }
    // Handle error or return a default/empty level data structure
    return (LevelData){0}; 
}
