#ifndef HEADER_H
#define HEADER_H
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h" 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


#define WINDOW_WIDTH    1920
#define WINDOW_HEIGHT   1080

#define BUTTON_SIZE_X 360
#define BUTTON_SIZE_Y 115

bool game_over (SDL_Event, SDL_Renderer *, bool);

//////////////////////////////////////
//MENU BUTTONS
//////////////////////////////////////
bool menu(SDL_Renderer *, bool);
#define TITLE_SIZE_X 1300
#define TITLE_SIZE_Y 135

#define TITLE_X 340
#define TITLE_Y 100

#define INFO_TERMINAL_SIZE_X 759
#define INFO_TERMINAL_SIZE_Y 384

#define INFO_TERMINAL_X 100
#define INFO_TERMINAL_Y 500

#define START_X 1400
#define START_Y 500

#define SETTINGS_X 1400
#define SETTINGS_Y 635

#define EXIT_X 1400
#define EXIT_Y 770
//////////////////////////////////////
//MUSIC BUTTONS
//////////////////////////////////////
void music(SDL_Event,SDL_Renderer *, bool);
#define MUSIC_TITLE_SIZE_X 506
#define MUSIC_TITLE_SIZE_Y 134

#define MUSIC_TITLE_X 707
#define MUSIC_TITLE_Y 100

#define BACK_X 780
#define BACK_Y 800

#define MUSIC1_X 250
#define MUSIC1_Y 300

#define MUSIC2_X 250
#define MUSIC2_Y 450

#define MUSIC3_X 250
#define MUSIC3_Y 600

#define MUSIC4_X 780
#define MUSIC4_Y 300

#define MUSIC5_X 780
#define MUSIC5_Y 450

#define MUSIC6_X 780
#define MUSIC6_Y 600

#define MUSIC7_X 1310
#define MUSIC7_Y 300

#define MUSIC8_X 1310
#define MUSIC8_Y 450

#define MUSIC9_X 1310
#define MUSIC9_Y 600

//////////////////////////////////////
//SETTINGS BUTTONS
//////////////////////////////////////
void settings(SDL_Event,SDL_Renderer *, bool);
#define SETTINGS_TITLE_SIZE_X 832
#define SETTINGS_TITLE_SIZE_Y 134

#define SETTINGS_TITLE_X 544
#define SETTINGS_TITLE_Y 100

#define BACK_X 780
#define BACK_Y 800

#define SOUNDS_X 320
#define SOUNDS_Y 450

#define SOUNDSOFF_X 320
#define SOUNDSOFF_Y 450

#define MUSIC_SET_X 780
#define MUSIC_SET_Y 450

#define MUSICOFF_X 780
#define MUSICOFF_Y 450

#define MUSIC_X 1240
#define MUSIC_Y 450

//////////////////////////////////////
//PLAY
//////////////////////////////////////
void field (SDL_Event,SDL_Renderer *, bool);
#define PAUSE_BUTTON_SIZE_X 101
#define PAUSE_BUTTON_SIZE_Y 101

#define PAUSE_X 35
#define PAUSE_Y 35

/////////////////////////////////////
//ARE YOU SURE
//////////////////////////////////////
bool are_you_sure(SDL_Event, SDL_Renderer *, bool);
#define YES_X 450
#define YES_Y 549

#define NO_X 1057
#define NO_Y 549

//////////////////////////////////////
//MODE MENU
//////////////////////////////////////
void mode(SDL_Event,SDL_Renderer *, bool);
#define MODE_TITLE_SIZE_X 432
#define MODE_TITLE_SIZE_Y 134

#define MODE_TITLE_X 743
#define MODE_TITLE_Y 100

#define BACK_X 780
#define BACK_Y 800


SDL_Renderer *g_renderer;

typedef struct s_stack {
    void *data;
    int size;
    int capacity;
    int type_size;
} t_stack;

t_stack new_stack(int capacity, int type_size);
void stack_push(t_stack* stack, const void* data);
void* stack_pop(t_stack* stack);
void stack_clear(t_stack* stack);

typedef struct s_collider t_collider;

typedef enum ENTITY_TYPE {
    PLAYER,
    ENEMY,
    BULLET,
    SPRITE,
    HP_DROP
}   e_etype;

typedef struct s_entity {
    float x, y;
    int index;
    bool active;
    void* data;
    void (*update) (struct s_entity *entity);
    void (*on_collision) (struct s_entity *this, struct s_entity *other);
    t_collider* collider;
    e_etype etype;
}   t_entity;

//////////////////////////////////////
//PAUSE MENU
//////////////////////////////////////
bool pause_menu (SDL_Event, SDL_Renderer *, bool,  SDL_Texture*, SDL_Texture*, SDL_Rect, SDL_Rect);
#define CONTINUE_X 780
#define CONTINUE_Y 310

#define PAUSE_SETTINGS_X 780
#define PAUSE_SETTINGS_Y 445

#define BACK_TO_MENU_X 780
#define BACK_TO_MENU_Y 580

#define ENTITY_POOL_SIZE 2048
#define COLLIDER_POOL_SIZE 2048
t_entity* entity_pool;
t_stack free_entity_pool_slots;

void entity_pool_free(t_entity* entity);
void entity_init(void);
t_entity* entity_pool_get(int x, int y, e_etype);
void entity_update(void);
void keep_on_screen(t_entity* entity);

typedef struct s_collider {
    bool active;
    int index;
    int offsetx, offsety, width, height;
    t_stack collisions;
    t_entity* owner;
}   t_collider;

t_collider* collider_pool;
t_stack free_collider_pool_slots;

void colliders_init(void);
void collider_pool_free(t_collider* collider);
void entity_pool_clear(void);
t_collider* collider_pool_get(t_entity* owner, int x, int y, int w, int h);

extern bool is_key_pressed[4096];
extern bool is_button_pressed[32];
extern bool button_was_pressed[32];
extern int mousex;
extern int mousey;
void input_pool_events();

typedef struct s_stats {
    int hp;
    int maxhp;
    int speed;
    int damage;
    int reloadtime;
    int reloadtimer;
    int timer;
    int scalefactor;
    SDL_Texture* texture;
    void (*on_motion)(t_entity* entity);
    void (*on_shoot)(t_entity* entity);
    int w, h;
}   t_stats;

t_entity* create_player(void);
t_entity* create_enemy(int x, int y, SDL_Texture* texture, void (*movement)(t_entity*), int scalefactor, void (*shoot)(t_entity*));
t_entity* g_player;

typedef enum TEAM {
    PLAYER_TEAM,
    ENEMY_TEAM
}   e_team;

typedef struct s_bullet {
    int size;
    int ttl;
    int vx, vy;
    e_team team;
    SDL_Texture* texture;
    int damage;

}   t_bullet;

t_entity* new_bullet(e_team team, int x, int y, int vx, int vy, SDL_Texture* texture, int damage, int size, int ttl);
t_entity* new_sprite(int x, int y, SDL_Texture* texture, int frames, int animation_delay, bool destroy_on_animation_end, SDL_Rect scale, SDL_Rect animrect);

void resolve_collisions(void);
void check_collisions(void);

void enemy_movement_diagonal_left_to_right (t_entity* enemy);
void enemy_movement_diagonal_right_to_left (t_entity* enemy);
void enemy_movement_slide_from_the_left(t_entity* enemy);
void enemy_movement_slide_from_the_right(t_entity* enemy);
void enemy_movement_straight (t_entity* enemy);
void boss_movement(t_entity* enemy);

//textures
void textures_init();
SDL_Texture* bullet_texture;
SDL_Texture* blue_bullet_texture;
SDL_Texture* player_texture;
SDL_Texture* enemy_texture_v1;
SDL_Texture* enemy_texture_v2;
SDL_Texture* enemy_texture_v3;
SDL_Texture* explosion_texture;
SDL_Texture* hp_texture;
SDL_Texture* boss_texture;
SDL_Texture* repair_texture;
//stages
typedef struct s_stage_entry {
    int x, y;
    t_stats* enemy_data;
    int delay;
    void(*on_motion)(t_entity*);
}   t_stage_entry;

void stages_update();
void init_stages();
//SOUNDS

Mix_Chunk *FIRE;
Mix_Chunk *LAZER;
Mix_Chunk *CLICK;

t_entity* new_drop(int x, int y);

t_entity* g_boss;

bool boss_come (SDL_Renderer *);
bool ending (SDL_Renderer *);

#endif

