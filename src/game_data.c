#include "game_data.h"
#include <stdio.h>   
#include <stdlib.h>
#include <string.h>












char *GetLevelPath(int levelID) {
    static char path[30];
    sprintf(path, "assets/levels/%d.lvl", levelID);
    return path;
}
LevelData* LoadLevelData(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening level file");
        return NULL;
    }

    LevelData *levelData = (LevelData*)malloc(sizeof(LevelData));
    if (levelData == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for LevelData.\n");
        fclose(file);
        return NULL;
    }
    // Initialize pointers to NULL for safety
    levelData->batch = NULL;

    char line[256];
    
    // 1. Skip the first comment line (e.g., "//level_0.lvl")
    if (fgets(line, sizeof(line), file) == NULL) { goto error_cleanup; }

    // 2. Read map width and height
    if (fscanf(file, "%d %d", &levelData->mapWidth, &levelData->mapHeight) != 2) { 
        fprintf(stderr, "Error reading map width and height.\n"); 
        goto error_cleanup; 
    }
    
    // Check if dimensions exceed the static array size
    if (levelData->mapWidth > 128 || levelData->mapHeight > 128) {
        fprintf(stderr, "Error: Map dimensions (%dx%d) exceed maximum supported size (128x128).\n", 
                levelData->mapWidth, levelData->mapHeight);
        goto error_cleanup;
    }
    
    // Skip the next comment line (e.g., "//tilemap:")
    while (fgets(line, sizeof(line), file) != NULL) {
        // Find the line that starts with "//tilemap:"
        if (strstr(line, "//tilemap:") != NULL) {
            break;
        }
    }
    
    // 3. Read the tilemap data
    for (int y = 0; y < levelData->mapHeight; y++) {
        for (int x = 0; x < levelData->mapWidth; x++) {
            int tileValue;
            if (fscanf(file, "%d", &tileValue) != 1) {
                fprintf(stderr, "Error reading tile at position (%d, %d).\n", x, y);
                goto error_cleanup;
            }
            levelData->map[y][x] = (byte)tileValue;
        }
    }
    
    // 4. Read the number of enemy batches (levelData->batchCount)
    if (fscanf(file, "%d", &levelData->batchCount) != 1) {
        fprintf(stderr, "Error reading batch count.\n");
        goto error_cleanup;
    }

    // Allocate memory for the batches
    levelData->batch = (Batch*)malloc(levelData->batchCount * sizeof(Batch));
    if (levelData->batch == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for Batches.\n");
        goto error_cleanup;
    }
    //printf("batch count: %d", levelData->batchCount);
    // 5. Read data for each batch
    for (int i = 0; i < levelData->batchCount; i++) {
        Batch *currentBatch = &levelData->batch[i];
        
        // Skip the next comment (e.g., "//number of enemy batches")
if (fgets(line, sizeof(line), file) == NULL) { goto error_cleanup; }
        // Read number of enemies in batch (enemyCount)
        if (fscanf(file, "%d", &currentBatch->enemyCount) != 1) {
            fprintf(stderr, "Error reading enemy count for batch %d.\n", i);
            goto error_cleanup;
        }

        // Allocate memory for the enemies in this batch
        currentBatch->enemies = (Entity*)malloc(currentBatch->enemyCount * sizeof(Entity));
        if (currentBatch->enemies == NULL) {
            fprintf(stderr, "Error: Could not allocate memory for enemies in batch %d.\n", i);
            goto error_cleanup;
        }
        
        // Read data for each enemy in the batch
        for (int j = 0; j < currentBatch->enemyCount; j++) {
            Entity *currentEnemy = &currentBatch->enemies[j];
if (fgets(line, sizeof(line), file) == NULL) { goto error_cleanup; }
            // Read enemy x, y
            if (fscanf(file, "%d %d", &currentEnemy->x, &currentEnemy->y) != 2) {
                fprintf(stderr, "Error reading position for enemy %d in batch %d.\n", j, i);
                goto error_cleanup;
            }
if (fgets(line, sizeof(line), file) == NULL) { goto error_cleanup; }
            // Read enemy type
            if (fscanf(file, "%d", &currentEnemy->type) != 1) {
                fprintf(stderr, "Error reading type for enemy %d in batch %d.\n", j, i);
                goto error_cleanup;
            }
        }
    }

    fclose(file);
    return levelData;

error_cleanup:
    // This cleans up memory if any error occurred during loading
    if (levelData) {
        FreeLevelData(levelData);
    }
    if (file) {
        fclose(file);
    }
    return NULL;
}




void FreeLevelData(LevelData* levelData) {
    if (levelData == NULL) return;

    // Free all enemy arrays within each batch
    if (levelData->batch != NULL) {
        for (int i = 0; i < levelData->batchCount; i++) {
            free(levelData->batch[i].enemies);
            levelData->batch[i].enemies = NULL;
        }
        // Free the array of batches itself
        free(levelData->batch);
        levelData->batch = NULL;
    }

    // Free the LevelData structure
    free(levelData);
}



void PrintLevelData(const LevelData* levelData) {
    if (levelData == NULL) {
        printf("Level Data is NULL.\n");
        return;
    }

    printf("## Map Data ##\n");
    printf("Map Dimensions: %d x %d\n", levelData->mapWidth, levelData->mapHeight);
    
    // Print a small snippet of the map for brevity
    printf("Tilemap (Top-Left 5x5):\n");
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (y < levelData->mapHeight && x < levelData->mapWidth) {
                printf("%3d", levelData->map[y][x]);
            }
        }
        printf("\n");
    }
    printf("...\n");

    printf("\n## Enemy Data ##\n");
    printf("Batch Count: %d\n", levelData->batchCount);

    for (int i = 0; i < levelData->batchCount; i++) {
        const Batch *batch = &levelData->batch[i];
        printf("  - Batch %d:\n", i);
        printf("    Enemy Count: %d\n", batch->enemyCount);
        
        for (int j = 0; j < batch->enemyCount; j++) {
            const Entity *enemy = &batch->enemies[j];
            printf("      Enemy %d: Pos=(%d, %d), Type=%d\n", j, enemy->x, enemy->y, enemy->type);
        }
    }
}










