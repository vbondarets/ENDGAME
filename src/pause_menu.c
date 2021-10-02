#include <../inc/header.h>

bool pause_menu (SDL_Event event, SDL_Renderer *renderer, bool running, 
                SDL_Texture* background, SDL_Texture* backstars, SDL_Rect back_coor, 
                SDL_Rect back_coor1){

    //SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/bg1.png");
    SDL_Texture* paused = IMG_LoadTexture(renderer, "./resource/textures/background/paused.png");
    SDL_Texture* continue_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/continue_button.png");
    SDL_Texture* settings_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/settings_button.png");
    SDL_Texture* back_to_menu_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/menu_button.png");

    SDL_Rect continue_rect = {CONTINUE_X, CONTINUE_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect settings_rect = {PAUSE_SETTINGS_X, PAUSE_SETTINGS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect back_to_menu_rect = {BACK_TO_MENU_X, BACK_TO_MENU_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    
    SDL_RenderCopy(renderer, background, NULL, &back_coor);
    SDL_RenderCopy(renderer, backstars, NULL, &back_coor1);
    entity_update();
    SDL_RenderCopy(renderer, paused, NULL, NULL);
    SDL_RenderCopy(renderer, continue_button, NULL, &continue_rect);
    SDL_RenderCopy(renderer, settings_button, NULL, &settings_rect);
    SDL_RenderCopy(renderer, back_to_menu_button, NULL, &back_to_menu_rect);
    SDL_RenderPresent(renderer);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= CONTINUE_X
                    && event.button.x <= CONTINUE_X + BUTTON_SIZE_X
                    && event.button.y >= CONTINUE_Y
                    && event.button.y <= CONTINUE_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        running = true;      
                        return running;             
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= PAUSE_SETTINGS_X
                    && event.button.x <= PAUSE_SETTINGS_X + BUTTON_SIZE_X
                    && event.button.y >= PAUSE_SETTINGS_Y
                    && event.button.y <= PAUSE_SETTINGS_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        settings(event,renderer, running);                  
                        SDL_RenderCopy(renderer, background, NULL, &back_coor);
                        SDL_RenderCopy(renderer, backstars, NULL, &back_coor1);
                        entity_update();
                        SDL_RenderCopy(renderer, paused, NULL, NULL);
                        SDL_RenderCopy(renderer, continue_button, NULL, &continue_rect);
                        SDL_RenderCopy(renderer, settings_button, NULL, &settings_rect);
                        SDL_RenderCopy(renderer, back_to_menu_button, NULL, &back_to_menu_rect);
                        SDL_RenderPresent(renderer); 
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= BACK_TO_MENU_X
                    && event.button.x <= BACK_TO_MENU_X + BUTTON_SIZE_X
                    && event.button.y >= BACK_TO_MENU_Y
                    && event.button.y <= BACK_TO_MENU_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        running = false;
                        break;
                    }         
                    break;
            }
        }
        
    }
    return running;
}

