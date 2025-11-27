#ifndef ENTITIES_H
#define ENTITIES_H

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define PROJECTILE_CAP 99
#define ALIENS_CAP 99
#define MIN_TIME_PROJ 1.0f
#define MIN_TIME_MELEE 0.5f
#define LIFE_TIME_MELEE 0.5f
#define MAX_I_TIME 0.6            //Inmunity time for aliens, must be greater than LIFE_TIME_MELEE
#define PLAYER_MAX_I_TIME 1.0f
#define ALIEN_DAMAGE 2           //Damage dealt by aliens to player
#define PROJECTILE_SPEED 100

//Define enemy types
#define PLAYER 1
#define ALIEN_PATROL 2
#define ALIEN_GUARD 3
#define PROJECTILE 4
#define MELEE 5

#define PATROL_LIMIT 64           //Patrol limit for alien patrol

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
    float hp; 
    float i_time;
    float initial_x_position;
    Texture2D current_texture; //Says what texture will be drawn 
    Rectangle dest_rect; 
    unsigned char state;
    int type;
    //for future versions there should be an enemy type flag
    int patrol_direction;
    int patrol_counter;
    int patrol_limit;
    int patrol_start_x;
} Entity; 

typedef struct entity_array {
    Entity* data;
    int size;
    int cap;
} entity_array;

entity_array init_ent_array(int capacity);
Entity CreateAlien(int type, float x, float y);
void add_alien(entity_array* arr, int type, float xposition, float yposition);
void add_projectile(entity_array* arr, Entity* player);

void move_projectile(Entity* proj);

Entity initialize_melee();
void spawn_melee(Entity* melee, Entity* player);
void colision_projectile_alien(Entity* alien, entity_array* proj_array);
void colision_melee_alien(Entity* alien, Entity* melee);
void move_alien_patrol(Entity* alien);
#endif

