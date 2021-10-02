#include <../inc/header.h>

bool menu (SDL_Renderer *renderer, bool running){

    SDL_Event event;

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/bg1.png");
    SDL_Texture* title = IMG_LoadTexture(renderer, "./resource/textures/background/star_defender.png");
    SDL_Texture* info_terminal = IMG_LoadTexture(renderer, "./resource/textures/background/info_terminal.png");
    SDL_Texture* start_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/start_button.png");
    SDL_Texture* settings_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/settings_button.png");
    SDL_Texture* exit_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/exit_button.png");
    
    SDL_Rect title_rect = {TITLE_X, TITLE_Y, TITLE_SIZE_X, TITLE_SIZE_Y};
    SDL_Rect info_terminal_rect = {INFO_TERMINAL_X, INFO_TERMINAL_Y, INFO_TERMINAL_SIZE_X, INFO_TERMINAL_SIZE_Y};
    SDL_Rect start_rect = {START_X, START_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect settings_rect = {SETTINGS_X, SETTINGS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect exit_rect = {EXIT_X, EXIT_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};

    while (running)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, title, NULL, &title_rect);
        SDL_RenderCopy(renderer, info_terminal, NULL, &info_terminal_rect);
        SDL_RenderCopy(renderer, start_button, NULL, &start_rect);
        SDL_RenderCopy(renderer, settings_button, NULL, &settings_rect);
        SDL_RenderCopy(renderer, exit_button, NULL, &exit_rect);

        entity_init();
        colliders_init();  
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= START_X
                    && event.button.x <= START_X + BUTTON_SIZE_X
                    && event.button.y >= START_Y
                    && event.button.y <= START_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        field(event,renderer, running);    
                        entity_pool_clear();              
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= SETTINGS_X
                    && event.button.x <= SETTINGS_X + BUTTON_SIZE_X
                    && event.button.y >= SETTINGS_Y
                    && event.button.y <= SETTINGS_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        settings(event,renderer, running);                    
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= EXIT_X
                    && event.button.x <= EXIT_X + BUTTON_SIZE_X
                    && event.button.y >= EXIT_Y
                    && event.button.y <= EXIT_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        running = are_you_sure(event,renderer, running);                     
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (event.motion.x >= START_X
                    && event.motion.x <= START_X + BUTTON_SIZE_X
                    && event.motion.y >= START_Y
                    && event.motion.y <= START_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(start_button, 200, 200, 200);
                        break;
                    }
                    if (event.motion.x >= SETTINGS_X
                    && event.motion.x <= SETTINGS_X + BUTTON_SIZE_X
                    && event.motion.y >= SETTINGS_Y
                    && event.motion.y <= SETTINGS_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(settings_button, 200, 200, 200);
                        break;
                    }
                    if (event.motion.x >= EXIT_X
                    && event.motion.x <= EXIT_X + BUTTON_SIZE_X
                    && event.motion.y >= EXIT_Y
                    && event.motion.y <= EXIT_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(exit_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(start_button, 255, 255, 255);
                    SDL_SetTextureColorMod(settings_button, 255, 255, 255);
                    SDL_SetTextureColorMod(exit_button, 255, 255, 255);
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return running;
}

