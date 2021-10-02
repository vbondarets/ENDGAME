#include "header.h"
typedef struct s_sprite {
    int timer;
    int animation_frames;
    int animation_delay;
    bool destroy_on_animation_end;
    SDL_Texture* texture;
    SDL_Rect animrect;
    SDL_Rect scale;
}   t_sprite;

void sprite_update(t_entity* sprite) {
    t_sprite* sprite_data = (t_sprite*)(sprite->data);
    SDL_Rect animrect = {0, 0, 96, 96};//sprite_data->scale;
    animrect.x = animrect.w * ((sprite_data->timer / sprite_data->animation_delay) % sprite_data->animation_frames);
    SDL_Rect rect = sprite_data->scale;;
    rect.x += sprite->x;
    rect.y += sprite->y;
    SDL_RenderCopy(g_renderer, sprite_data->texture, &animrect, &rect);
    sprite_data->timer++;

    if(sprite_data->timer >= sprite_data->animation_delay * sprite_data->animation_frames) {
        entity_pool_free(sprite);
    }
}


t_entity* new_sprite(int x, int y, SDL_Texture* texture, int frames, int animation_delay, bool destroy_on_animation_end, SDL_Rect scale, SDL_Rect animrect) {
    t_entity* sprite = entity_pool_get(x, y, SPRITE);
    t_sprite* sprite_data = malloc(sizeof(t_sprite));
    sprite_data->timer = 0;
    sprite_data->animation_frames = frames;
    sprite_data->animation_delay = animation_delay;
    sprite_data->destroy_on_animation_end = destroy_on_animation_end;
    sprite_data->scale = scale;
    sprite_data->animrect = animrect;
    sprite_data->texture = texture;

    sprite->data = sprite_data;
    sprite->update = &sprite_update;

    return sprite;
}

