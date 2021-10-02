#include "header.h"


t_stats enemy_stats_v1;
t_stats enemy_stats_v2;
t_stats enemy_stats_v3;
t_stats boss_stats;
t_stage_entry stage_entries[5000];

int make_entry_iterator = 0;

void make_entry(int x, int y, t_stats* stats, int delay, void(*on_motion)(t_entity*)){
    t_stage_entry entry = {x, y, stats, delay, on_motion};
    stage_entries[make_entry_iterator] = entry;
    make_entry_iterator++;
}

/*
typedef struct s_stats {
    int hp;
    int maxhp;
    int speed;
    int damage;
    int reloadtime;
    int reloadtimer;
    int timer;
    SDL_Texture* texture;
    void (*on_motion)(t_entity* entity);
    int w, h;
}   t_stats;
*/

t_stats make_stats(int hp, int speed, int damage, int reloadtime, SDL_Texture* texture, int scalefactor, void(*shoot)(t_entity*)) {
    t_stats stats = {hp, hp, speed, damage, reloadtime, 0, 0, scalefactor, texture, NULL, shoot, 0, 0};
    return stats;
}

int stage_timer = 0;
int stage_delay = 0;
int stage_step = 0;

void boss_shooting(t_entity* boss) {
    t_stats* boss_data = boss->data;

    int attack_timer = boss_data->timer / 120;

    if(attack_timer % 2) {
        new_bullet(ENEMY_TEAM, boss->x, boss->y, 8, 16, bullet_texture, boss_data->damage / 2, 32, 600);
        new_bullet(ENEMY_TEAM, boss->x, boss->y, -8, 16, bullet_texture, boss_data->damage / 2, 32, 600);
    }

    new_bullet(ENEMY_TEAM, boss->x, boss->y, 0, 16, bullet_texture, boss_data->damage, 48, 600);
}

int boss_index = 0;

void init_stages() {
    //hp, speed, damage, reloadtime, texture
    enemy_stats_v1 = make_stats(6, 1, 1, 150, enemy_texture_v2, 4, NULL);
    enemy_stats_v2 = make_stats(3, 2, 1, 100, enemy_texture_v1, 4, NULL);
    enemy_stats_v3 = make_stats(4, 4, 1, 50, enemy_texture_v3, 4, NULL);
    boss_stats = make_stats(100, 1, 2, 50, boss_texture, 3, &boss_shooting);


    //make_entry(WINDOW_WIDTH / 2, -128, &boss_stats, 0, &enemy_movement_straight);
    //stage 1
    //x, y, stats, delay, movement
    g_boss = NULL;

    make_entry(WINDOW_WIDTH / 2, -128, &enemy_stats_v2, 120, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 1, -128, &enemy_stats_v1, 50, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 3, -128, &enemy_stats_v1, 50, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 5, -128, &enemy_stats_v1, 50, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 7, -128, &enemy_stats_v1, 50, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 9, -128, &enemy_stats_v1, 50, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v3, 0, &enemy_movement_diagonal_right_to_left);
    make_entry(-128, -64, &enemy_stats_v3, 100, &enemy_movement_diagonal_left_to_right);
    make_entry(-128, -64, &enemy_stats_v2, 100, &enemy_movement_slide_from_the_left);
    make_entry(-128, -64, &enemy_stats_v2, 100, &enemy_movement_slide_from_the_left);
    make_entry(-128, -64, &enemy_stats_v2, 50, &enemy_movement_slide_from_the_left);

    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v2, 100, &enemy_movement_slide_from_the_right);
    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v2, 100, &enemy_movement_slide_from_the_right);
    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v2, 500, &enemy_movement_slide_from_the_right);


    make_entry(WINDOW_WIDTH / 10 * 5, -128, &enemy_stats_v2, 100, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 7, -128, &enemy_stats_v2, 0, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 3, -128, &enemy_stats_v2, 100, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 9, -128, &enemy_stats_v2, 0, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 1, -128, &enemy_stats_v2, 500, &enemy_movement_straight);

    make_entry(WINDOW_WIDTH / 10 * 1, -128, &enemy_stats_v2, 0, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 9, -128, &enemy_stats_v2, 100, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 3, -128, &enemy_stats_v2, 0, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 7, -128, &enemy_stats_v2, 100, &enemy_movement_straight);
    make_entry(WINDOW_WIDTH / 10 * 5, -128, &enemy_stats_v2, 300, &enemy_movement_straight);

    //slides
    make_entry(-128, -64, &enemy_stats_v1, 0, &enemy_movement_slide_from_the_left);
    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v1, 150, &enemy_movement_slide_from_the_right);
    make_entry(-128, -64, &enemy_stats_v1, 0, &enemy_movement_slide_from_the_left);
    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v1, 150, &enemy_movement_slide_from_the_right);

    make_entry(WINDOW_WIDTH + 128, -64, &enemy_stats_v2, 500, &enemy_movement_slide_from_the_right);

    boss_index = make_entry_iterator;
    make_entry(WINDOW_WIDTH / 2, -128, &boss_stats, 0, &boss_movement);

    for(int i = 0; i < 120; i++) {
        int statrand = rand() % 3;
        int moverand = rand() % 5;

        void(*moverandptr)(t_entity*);

        if(moverand == 0)
            moverandptr = &enemy_movement_straight;
        if(moverand == 1)
            moverandptr = &enemy_movement_diagonal_right_to_left;
        if(moverand == 2)
            moverandptr = &enemy_movement_diagonal_left_to_right;
        if(moverand == 3)
            moverandptr = &enemy_movement_slide_from_the_right;
        if(moverand == 4)
            moverandptr = &enemy_movement_slide_from_the_left;

        t_stats* randstatptr = &enemy_stats_v1;
        if(statrand == 1)
            randstatptr = &enemy_stats_v2;
        if(statrand == 2)
            randstatptr = &enemy_stats_v3;
        
        make_entry(rand() % (WINDOW_WIDTH - 128) + 64, -64, randstatptr, rand() % 150 + 120, moverandptr);
    }

    make_entry(0, 0, NULL, 0, NULL);

    stage_timer = 0;
    stage_delay = 0;
    stage_step = 0;
}




void stages_update() {

    stage_timer++;
    if(stage_timer > stage_delay) {
        stage_timer = 0;
        if(stage_entries[stage_step].enemy_data) {
            t_stage_entry entry = stage_entries[stage_step];
            stage_delay = entry.delay;
            t_entity* enemy = create_enemy(entry.x, entry.y, entry.enemy_data->texture, entry.on_motion, entry.enemy_data->scalefactor, entry.enemy_data->on_shoot);
            t_stats* enemy_data = (t_stats*)(enemy->data);
            enemy_data->hp = entry.enemy_data->hp;
            enemy_data->maxhp = enemy_data->maxhp;
            enemy_data->speed = entry.enemy_data->speed;
            enemy_data->damage = entry.enemy_data->damage;
            enemy_data->reloadtime = entry.enemy_data->reloadtime;
            enemy_data->scalefactor = entry.enemy_data->scalefactor;

            if(stage_step == boss_index) {
                g_boss = enemy;
            }
        }
        stage_step++;
    }

}

