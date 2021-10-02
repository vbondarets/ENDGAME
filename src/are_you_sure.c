#include "header.h"

bool are_you_sure (SDL_Event event, SDL_Renderer *renderer, bool running){

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/bg1.png");
    SDL_Texture* background1 = IMG_LoadTexture(renderer, "./resource/textures/background/zatemnenie copy.png");
    SDL_Texture* are_u_shure = IMG_LoadTexture(renderer, "./resource/textures/background/sure_.png");
    SDL_Texture* yes_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/yes_button.png");
    SDL_Texture* no_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/no_button.png");
    
    SDL_Rect yes_rect = {YES_X, YES_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect no_rect = {NO_X, NO_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    
    Mix_Chunk *CLICK = Mix_LoadWAV("./resource/music/klik.wav");

    while (running)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, background1, NULL, NULL);
        SDL_RenderCopy(renderer, are_u_shure, NULL, NULL);
        SDL_RenderCopy(renderer, yes_button, NULL, &yes_rect);
        SDL_RenderCopy(renderer, no_button, NULL, &no_rect);

         while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= YES_X
                    && event.button.x <= YES_X + BUTTON_SIZE_X
                    && event.button.y >= YES_Y
                    && event.button.y <= YES_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(400);
                        running = false;                     
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= NO_X
                    && event.button.x <= NO_X + BUTTON_SIZE_X
                    && event.button.y >= NO_Y
                    && event.button.y <= NO_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(400);
                        running = false;                  
                        return running = true;
                    }
                                       
                    break;

                case SDL_MOUSEMOTION:
                    if (event.motion.x >= YES_X
                    && event.motion.x <= YES_X + BUTTON_SIZE_X
                    && event.motion.y >= YES_Y
                    && event.motion.y <= YES_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(yes_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(yes_button, 255, 255, 255);
                    if (event.motion.x >= NO_X
                    && event.motion.x <= NO_X + BUTTON_SIZE_X
                    && event.motion.y >= NO_Y
                    && event.motion.y <= NO_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(no_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(no_button, 255, 255, 255);

                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return running;
}

