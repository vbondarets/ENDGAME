#include "header.h"
void textures_init() {
    bullet_texture = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/bullet_of_spaceship.png");
    blue_bullet_texture = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/bullet_of_spaceship2.png");
    player_texture = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/stage3_spaceship.png");
    enemy_texture_v1 = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/basic_enemy_spaceship.png");
    enemy_texture_v2 = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/fat_enemy_spaceship.png");
    enemy_texture_v3 = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/general_enemy_spaceship.png");
    explosion_texture = IMG_LoadTexture(g_renderer, "./resource/textures/animations/effects/Explosion.png");
    hp_texture = player_texture;
    boss_texture = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/boss2_spaceship.png");
    repair_texture = IMG_LoadTexture(g_renderer, "./resource/textures/spaceships/spaceship_hp.png");
}

