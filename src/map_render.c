#include "map_render.h"


void renderMap (LevelData *level, Texture2D floorTile, Texture2D wallTile) {

    Color white = { 255, 255, 255, 255.0f };

	// The Rendering Loop
    for (int y = 0; y < level->mapHeight; y++){
        for (int x = 0; x < level->mapWidth; x++){
			byte tile = level->map[y][x];
			if (tile == 1){
				DrawTexture(wallTile, 
				x*16, 
				y*16, white);
			}else{
				DrawTexture(floorTile, 
				x*16, 
				y*16, white);
			}
		}
	}
}

