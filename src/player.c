#include <../inc/header.h>

//SDL_Texture* bullet_texture = IMG_LoadTexture(g_renderer, "textures/spaceships/bullet_of_spaceship.png");
//SDL_RenderCopy(g_renderer, ((SDL_Texture*)(player->data)), NULL, &rect);

void player_update(t_entity* player) {

    t_stats* player_data = (t_stats*)(player->data);
    
    
    keep_on_screen(player);
    player_data->on_motion(player);
    

    SDL_Rect rect = {player->x - player_data->w / 2, player->y - player_data->h / 2, player_data->w, player_data->h};
    SDL_RenderCopy(g_renderer, player_data->texture, NULL, &rect);

    player_data->reloadtimer++;
    if(player_data->reloadtimer > player_data->reloadtime) {
        if(is_key_pressed[SDLK_SPACE]) {
            Mix_PlayChannel(-1, LAZER, 0);
            new_bullet(PLAYER_TEAM, player->x, player->y, 0, -16, blue_bullet_texture, player_data->damage, 32, 600);
            player_data->reloadtimer = 0;
        }
    }

    if(player_data->hp <= 0) {
        g_player = NULL;
        SDL_Rect scale = {-96, -96, 192, 192};
        SDL_Rect anim = {0, 0, 96, 96};
        Mix_PlayChannel(-1, FIRE, 0);
        new_sprite(player->x, player->y, explosion_texture, 12, 3, true, scale, anim);
        entity_pool_free(player);
        //on_player_death();
    }
    
}

void player_movement(t_entity* player) {
    t_stats* player_data = (t_stats*)player->data;

    if(is_key_pressed[SDLK_w]) {
        player->y -= player_data->speed;
    }
    if(is_key_pressed[SDLK_a]) {
        player->x -= player_data->speed;
    }
    if(is_key_pressed[SDLK_s]) {
        player->y += player_data->speed;
    }
    if(is_key_pressed[SDLK_d]) {
        player->x += player_data->speed;
    }
}

void player_on_collision (t_entity* shipA, t_entity* shipB) {
    if(shipB->etype == ENEMY) {
        t_stats* statA = (t_stats*)(shipA->data);
        t_stats* statB = (t_stats*)(shipB->data);
        statA->hp--;
        statB->hp--;
        SDL_Rect scale = {-32, -32, 64, 64};
        SDL_Rect anim = {0, 0, 96, 96};
        new_sprite(shipA->x + rand() % (statA->w) - statA->w / 2, shipA->y + rand() % (statA->h) - statA->h / 2, explosion_texture, 12, 3, true, scale, anim);
        new_sprite(shipB->x + rand() % (statB->w) - statB->w / 2, shipB->y + rand() % (statB->h) - statB->h / 2, explosion_texture, 12, 3, true, scale, anim);
    }
}

t_entity* create_player(void) {
    
    //SDL_Texture* bullet_texture = IMG_LoadTexture(g_renderer, "textures/spaceships/bullet_of_spaceship.png");
    t_entity* player = entity_pool_get(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, PLAYER);
    player->update = &player_update;
    t_stats* player_data = malloc(sizeof(t_stats));
    player_data->reloadtime = 10;
    player_data->reloadtimer = 0;
    player_data->hp = 10;
    player_data->maxhp = 10;
    player_data->damage = 1;
    player_data->speed = 6;
    player_data->texture = player_texture;
    player_data->on_motion = &player_movement;
    SDL_QueryTexture(player_data->texture, NULL, NULL, &player_data->w, &player_data->h);
    player_data->w *= 4;
    player_data->h *= 4;
    player->data = player_data;
    player->on_collision = &player_on_collision;
    collider_pool_get(player, -player_data->w / 2, -player_data->h / 2, player_data->w, player_data->h);
    
    return player;
}

