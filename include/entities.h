#ifndef ENTITIES_H
#define ENTITIES_H

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define PROJECTILE_CAP  5

#include <raylib.h> //The textures struct will be included inside the entity struct 
typedef struct Textures { 
    Texture2D texture_up; 
    Texture2D texture_down; 
    Texture2D texture_side; 
} Textures; 

//entity contains all entity info 
typedef struct Entity { 
    int vertical_direction; 
    int horizontal_direction;
    int current_direction;
    struct Textures textures; 
    Texture2D current_texture; //Says what texture will be drawn 
    Rectangle dest_rect; 
    float hp; 
} Entity; 

typedef struct entity_array {
    Entity* data;
    int size;
    int cap;
} entity_array;

entity_array init_ent_array(int capacity);
void add_projectile(entity_array* arr, Entity* player);

#endif

