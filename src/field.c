#include "../inc/header.h"

void field (SDL_Event event, SDL_Renderer *renderer, bool running){
    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/planet&stars.jpg");
    SDL_Texture* backstars = IMG_LoadTexture(renderer, "./resource/textures/background/planet&.jpg");
    SDL_Texture* pause_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/pause_button.png");
    SDL_Texture* intro = IMG_LoadTexture(renderer, "./resource/textures/animations/bg_intro/bg_intro.png");
    SDL_Texture* commander = IMG_LoadTexture(renderer, "./resource/textures/animations/bg_intro/commander_intro.png");
    SDL_Texture* text_panel = IMG_LoadTexture(renderer, "./resource/textures/animations/bg_intro/intro_text.png");

//750
    double o = 1080, y = 1080;
    SDL_RenderCopy(renderer, intro, NULL, NULL);
    double j = 1.5;
    int sec = 10000, fps = 15;
    int gameover_delay = 90;
    int boss_delay = 60;

    bool boss_has_been_spawned = false;

    while(y > 750)  {
        input_pool_events();
        if (is_key_pressed[SDLK_RETURN]){
        sec = 166;
        fps = 0;
        }
        SDL_Rect coor_comand = {0, y, 235, 358};
        SDL_RenderCopy(renderer, intro, NULL, NULL);
        SDL_RenderCopy(renderer, commander, NULL, &coor_comand);
        SDL_RenderPresent(renderer);
        y -= j;
        SDL_Delay(fps);
    }
    //800
    while(o > 800) {
        input_pool_events();
        if (is_key_pressed[SDLK_RETURN]){
        sec = 166;
        fps = 0;
        }
        SDL_RenderCopy(renderer, intro, NULL, NULL);
        SDL_Rect text_size = {260, o, 1600, 275};
        SDL_Rect coor_comand = {0, y, 235, 358};
        SDL_RenderCopy(renderer, commander, NULL, &coor_comand);
        SDL_RenderCopy(renderer, text_panel, NULL, &text_size);
        SDL_RenderPresent(renderer);
        o -= j;
        SDL_Delay(fps);
    }
    
    SDL_Delay(sec);

    SDL_Rect pause_rect = {PAUSE_X, PAUSE_Y, PAUSE_BUTTON_SIZE_X, PAUSE_BUTTON_SIZE_Y};
    double i = 0.25;
    double y1, y2;
    y1 = 0;
    y2 = -1080;

    g_player = create_player();
    t_stats* player_stats = (t_stats*)(g_player->data);
    init_stages();

    while (running) {
        if (y1 == 1080) {
            background = backstars;
            y1 = -1080;
        }
        if (y2 == 1080) {
            y2 = -1080;
        }
        SDL_Rect back_coor = {0, y1, 1920, 1080};
        SDL_Rect back_coor1 = {0, y2, 1920, 1080};
        y1 += i;
        y2 += i;
        SDL_RenderCopy(renderer, background, NULL, &back_coor);
        SDL_RenderCopy(renderer, backstars, NULL, &back_coor1);
        SDL_RenderCopy(renderer, pause_button, NULL, &pause_rect);
        

        input_pool_events();
        entity_update();
        check_collisions();
        resolve_collisions();
        stages_update();

        if (!g_player) {
            gameover_delay--;
            if(gameover_delay <= 0) {
                entity_pool_clear();
                game_over(event, renderer, running);
                return;
            }
        }


        if (is_button_pressed[SDL_BUTTON_LEFT]
        && mousex >= PAUSE_X
        && mousex <= PAUSE_X + PAUSE_BUTTON_SIZE_X
        && mousey >= PAUSE_Y
        && mousey <= PAUSE_Y + PAUSE_BUTTON_SIZE_Y) {
            Mix_PlayChannel(-1, CLICK, 0);
            SDL_Delay(250);
            SDL_RenderPresent(renderer);
            if(!pause_menu(event, renderer, running, background, backstars, back_coor, back_coor1)) {
                return;
            }
            is_button_pressed[SDL_BUTTON_LEFT] = false;
        }
        if(g_player) {
            for(int i = 1; i <= player_stats->hp; i++) {
                SDL_Rect hp_rect = {WINDOW_WIDTH - i * 48 - 32, 32, 32, 32};
                SDL_RenderCopy(renderer, hp_texture, NULL, &hp_rect);
            }
        }

        if(g_boss) {
            if(!boss_has_been_spawned) {
                boss_has_been_spawned = true;
                boss_come(renderer);
            }
        }
        else if (boss_has_been_spawned) {
            boss_delay--;
            if(boss_delay < 0) {
                ending (renderer);
                return;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
}

