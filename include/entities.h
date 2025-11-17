#ifndef ENTITIES_H
#define ENTITIES_H

#include <raylib.h> //The textures struct will be included inside the entity struct 
typedef struct textures { 
    Texture2D texture_up; 
    Texture2D texture_down; 
    Texture2D texture_side; 
} textures; 

//entity contains all entity info 
typedef struct entity { 
    float direction; 
    struct textures textures; 
    Texture2D current_texture; //Says what texture will be drawn 
    Rectangle dest_rect; 
    float hp; 
} entity; 

#endif

