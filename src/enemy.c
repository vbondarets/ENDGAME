#include <../inc/header.h>

void enemy_update(t_entity* enemy) {
    
    t_stats* enemy_data = (t_stats*)(enemy->data);

    enemy_data->timer++;

    SDL_Rect rect = {enemy->x - enemy_data->w / 2, enemy->y - enemy_data->h / 2, enemy_data->w, enemy_data->h};
    SDL_RenderCopy(g_renderer, enemy_data->texture, NULL, &rect);

    enemy_data->on_motion(enemy);

    enemy_data->reloadtimer++;
    if(enemy_data->reloadtimer > enemy_data->reloadtime) {
        enemy_data->reloadtimer = 0;
        if(enemy_data->on_shoot) {
            enemy_data->on_shoot(enemy);
        }
        else
            new_bullet(ENEMY_TEAM, enemy->x, enemy->y, 0, 16, bullet_texture, enemy_data->damage, 32, 600);
    }

    if(enemy_data->hp <= 0) {
        SDL_Rect scale = {-96, -96, 192, 192};
        SDL_Rect anim = {0, 0, 96, 96};
        Mix_PlayChannel(-1, FIRE, 0);
        new_sprite(enemy->x, enemy->y, explosion_texture, 12, 3, true, scale, anim);
        if(rand() % 2 == 0)
            new_drop(enemy->x, enemy->y);
        if(g_boss == enemy) {
            g_boss = NULL;
        }
        entity_pool_free(enemy);
    }

    if(enemy->y > WINDOW_HEIGHT + 256) {
        entity_pool_free(enemy);
    }
}

void enemy_movement_diagonal_left_to_right (t_entity* enemy) {
     t_stats* enemy_data = (t_stats*)(enemy->data);
     enemy->x += enemy_data->speed;
     enemy->y += enemy_data->speed;
}

void enemy_movement_diagonal_right_to_left (t_entity* enemy) {
     t_stats* enemy_data = (t_stats*)(enemy->data);
     enemy->x -= enemy_data->speed;
     enemy->y += enemy_data->speed;
}

void enemy_movement_straight (t_entity* enemy) {
    t_stats* enemy_data = (t_stats*)(enemy->data);
    enemy->y += enemy_data->speed;
}

void enemy_movement_slide_from_the_left (t_entity* enemy) {
    t_stats* enemy_data = (t_stats*)(enemy->data);
    float yp = ((enemy->y / (float)WINDOW_HEIGHT) * 2.0f - 1.0f);
    enemy->x = (float)WINDOW_WIDTH / 2 -  yp * yp * (float)WINDOW_WIDTH / 2.0f;
    enemy->y += enemy_data->speed;
}

void enemy_movement_slide_from_the_right (t_entity* enemy) {
    t_stats* enemy_data = (t_stats*)(enemy->data);
    float yp = ((enemy->y / (float)WINDOW_HEIGHT) * 2.0f - 1.0f);
    enemy->x = (float)WINDOW_WIDTH / 2 +  yp * yp * (float)WINDOW_WIDTH / 2.0f;
    enemy->y += enemy_data->speed;
}

void boss_movement(t_entity* enemy) {
    t_stats* enemy_data = (t_stats*)(enemy->data);
    float timer = (float)enemy_data->timer * (float)enemy_data->speed / 150.0f;
    enemy->x = (float)WINDOW_WIDTH / 2.0f + sin(timer) * (float)WINDOW_WIDTH / 2.3f;
    enemy->y = (sin(timer * 2.0f) / 2.0f + 0.5f) * (float)WINDOW_HEIGHT / 3.0f + 32.0f - 256 + (enemy_data->timer > 256 ? 256 : enemy_data->timer);
}

t_entity* create_enemy(int x, int y, SDL_Texture* texture, void (*movement)(t_entity*), int scalefactor, void (*shoot)(t_entity*)) {
    t_entity* enemy = entity_pool_get(x, y, ENEMY);
    enemy->update = &enemy_update;

    t_stats* enemy_data = malloc(sizeof(t_stats));
    enemy_data->texture = texture;
    enemy_data->reloadtimer = 0;
    enemy_data->timer = 0;
    SDL_QueryTexture(enemy_data->texture, NULL, NULL, &enemy_data->w, &enemy_data->h);
    enemy_data->w *= scalefactor;
    enemy_data->h *= scalefactor;
    enemy->data = enemy_data;
    enemy_data->on_motion = movement;
    enemy_data->on_shoot = shoot;
    collider_pool_get(enemy, -enemy_data->w / 2, -enemy_data->h / 2, enemy_data->w, enemy_data->h);
    return enemy;
}

