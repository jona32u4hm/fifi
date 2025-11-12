#include "level_data.h"

// The array index is the Level ID 
static LevelData levels[] = {
    {
        .mapFilePath = "assets/maps/level1.json",
        .mapWidth = 64,
        .enemyCount = 2,
        .enemies = {
            {.spawnPos = {100, 100}, .typeID = 0},
            {.spawnPos = {200, 100}, .typeID = 1}
        },
        .playerStart = {.startPos = {50, 50}}
    },
    
    {
        .mapFilePath = "assets/maps/level2.json",
        .mapWidth = 128,
        .enemyCount = 5,
        // ... define enemy setups for Level 2
    }
    // ... add more levels here
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
