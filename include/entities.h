#ifndef ENTITIES_H
#define ENTITIES_H

#include <raylib.h> //The textures struct will be included inside the entity struct 
typedef struct Textures { 
    Texture2D texture_up; 
    Texture2D texture_down; 
    Texture2D texture_side; 
} Textures; 

//entity contains all entity info 
typedef struct Entity { 
    float direction; 
    struct Textures textures; 
    Texture2D current_texture; //Says what texture will be drawn 
    Rectangle dest_rect; 
    float hp; 
} Entity; 

#endif

