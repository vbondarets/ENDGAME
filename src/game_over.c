#include <../inc/header.h>

bool game_over (SDL_Event event, SDL_Renderer *renderer, bool running){

    SDL_Texture* gameover = IMG_LoadTexture(renderer, "./resource/textures/background/game_over1.png");
    SDL_RenderCopy(renderer, gameover, NULL, NULL);
    SDL_RenderPresent(renderer);

    while (running)
    {
        while (SDL_PollEvent(&event)) {
             switch(event.type) {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_RETURN) {
                        return false;
                    }
                break;
            }
        }
    }
    return false;
}

