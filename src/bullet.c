#include "header.h"


void bullet_update(t_entity* bullet) {
    t_bullet* bullet_data = (t_bullet*)bullet->data;

    bullet->x += bullet_data->vx;
    bullet->y += bullet_data->vy;
    bullet_data->ttl--;
    if(bullet_data->ttl < 0) {

        entity_pool_free(bullet);
    }
    SDL_Rect rect = {bullet->x - bullet_data->size / 2, bullet->y - bullet_data->size / 2, bullet_data->size, bullet_data->size};
    SDL_RenderCopy(g_renderer, ((SDL_Texture*)(bullet_data->texture)), NULL, &rect);
}

void on_bullet_collision (t_entity* this, t_entity* other) {
    t_bullet* bullet_data = (t_bullet*)(this->data);
    if((other->etype == PLAYER && bullet_data->team != PLAYER_TEAM) || (other->etype == ENEMY && bullet_data->team != ENEMY_TEAM)) {
        t_stats* player_data = (t_stats*)other->data;
        player_data->hp -= bullet_data->damage;
        entity_pool_free(this);
        SDL_Rect scale = {-bullet_data->size, -bullet_data->size, bullet_data->size * 2, bullet_data->size * 2};
        SDL_Rect anim = {0, 0, 96, 96};
        new_sprite(this->x, this->y, explosion_texture, 12, 3, true, scale, anim);
    }
}

t_entity* new_bullet(e_team team, int x, int y, int vx, int vy, SDL_Texture* texture, int damage, int size, int ttl) {
    t_bullet* bullet_data = malloc(sizeof(t_bullet));
    bullet_data->team = team;
    bullet_data->vx = vx;
    bullet_data->vy = vy;
    bullet_data->texture = texture;
    bullet_data->damage = damage;
    bullet_data->size = size;
    bullet_data->ttl = ttl;

    t_entity* bullet_entity = entity_pool_get(x, y, BULLET);
    bullet_entity->data = bullet_data;
    bullet_entity->update = &bullet_update;
    bullet_entity->on_collision = &on_bullet_collision;

    collider_pool_get(bullet_entity, -size / 2, -size / 2, size, size);

    return bullet_entity;
}

