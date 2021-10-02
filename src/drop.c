#include "header.h"

void drop_update(t_entity* drop) {
    SDL_Rect rect = {drop->x - 32, drop->y - 32, 64, 64};
    SDL_RenderCopy(g_renderer, repair_texture, NULL, &rect);
    drop->y += 3;
}

void hp_pick(t_entity* this, t_entity* other) {
    if(other->etype == PLAYER) {
        ((t_stats*)(other->data))->hp += 2;
        if(((t_stats*)(other->data))->hp > ((t_stats*)(other->data))->maxhp) {
            ((t_stats*)(other->data))->hp = ((t_stats*)(other->data))->maxhp;
        }
        entity_pool_free(this);
    }
}

t_entity* new_drop(int x, int y) {
    t_entity* drop_entity = entity_pool_get(x, y, HP_DROP);
    drop_entity->update = &drop_update;
    drop_entity->on_collision = &hp_pick;
    collider_pool_get(drop_entity, -32, -32, 64, 64);
    return drop_entity;
}

