#include <../inc/header.h>

bool boss_come (SDL_Renderer *renderer) {


    SDL_Texture* commander = IMG_LoadTexture(renderer, "resource/textures/animations/bg_intro/commander_intro.png");
    SDL_Texture* text_panel = IMG_LoadTexture(renderer, "resource/textures/animations/bg_intro/boss_text.png");

    SDL_Rect coor_comand = {0, 750, 235, 358};
    SDL_Rect text_size = {260, 800, 1600, 275};
    
    SDL_RenderCopy(renderer, commander, NULL, &coor_comand);
    SDL_RenderCopy(renderer, text_panel, NULL, &text_size);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    while (true)
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

