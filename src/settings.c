#include <../inc/header.h>

void settings (SDL_Event event,SDL_Renderer *renderer, bool running){

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/bg1.png");
    SDL_Texture* settings_title = IMG_LoadTexture(renderer, "./resource/textures/background/settings_title.png");
    SDL_Texture* back_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/back_button.png");
    SDL_Texture* sounds_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/sounds_button.png");
    SDL_Texture* music_set_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music_button.png");
    SDL_Texture* music_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/tracks.png");
    SDL_Texture* musicoff_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/musicoff.png");
    SDL_Texture* soundsoff_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/soundsoff.png");
    
    static bool musics_button = true;   
    static bool sound_button= true;

    SDL_Texture* current_music_button = musics_button ? music_set_button : musicoff_button;
    SDL_Texture* current_sound_button = sound_button ? sounds_button : soundsoff_button;

    SDL_Rect settings_title_rect = {SETTINGS_TITLE_X, SETTINGS_TITLE_Y, SETTINGS_TITLE_SIZE_X, SETTINGS_TITLE_SIZE_Y};
    SDL_Rect back_rect = {BACK_X, BACK_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect sounds_rect = {SOUNDS_X, SOUNDS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music_set_rect = {MUSIC_SET_X, MUSIC_SET_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music_rect = {MUSIC_X, MUSIC_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};

    
    
    while (running)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, settings_title, NULL, &settings_title_rect);
        SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
        SDL_RenderCopy(renderer, current_sound_button, NULL, &sounds_rect);
        SDL_RenderCopy(renderer, current_music_button, NULL, &music_set_rect);
        SDL_RenderCopy(renderer, music_button, NULL, &music_rect);

         while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= BACK_X
                    && event.button.x <= BACK_X + BUTTON_SIZE_X
                    && event.button.y >= BACK_Y
                    && event.button.y <= BACK_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        running = false;                     
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC_X
                    && event.button.x <= MUSIC_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC_Y
                    && event.button.y <= MUSIC_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        music(event,renderer, running);                    
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC_SET_X
                    && event.button.x <= MUSIC_SET_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC_SET_Y
                    && event.button.y <= MUSIC_SET_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                            SDL_Delay(250);
                        if (musics_button){
                            current_music_button = musicoff_button;
                            musics_button = false;
                            Mix_PauseMusic();
                        }
                        else {
                            current_music_button = music_set_button;
                            musics_button = true;
                            Mix_ResumeMusic();
                        }
                        break;
                    }
                    else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= SOUNDS_X
                    && event.button.x <= SOUNDS_X + BUTTON_SIZE_X
                    && event.button.y >= SOUNDS_Y
                    && event.button.y <= SOUNDS_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if (sound_button){
                            Mix_Volume(-1, 0);
                            current_sound_button = soundsoff_button;
                            sound_button = false;
                        }
                        else {
                            Mix_Volume(-1, 128);
                            current_sound_button = sounds_button;
                            sound_button = true;
                        }
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.x >= BACK_X
                    && event.motion.x <= BACK_X + BUTTON_SIZE_X
                    && event.motion.y >= BACK_Y
                    && event.motion.y <= BACK_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(back_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(back_button, 255, 255, 255);
                    if (event.motion.x >= SOUNDS_X
                    && event.motion.x <= SOUNDS_X + BUTTON_SIZE_X
                    && event.motion.y >= SOUNDS_Y
                    && event.motion.y <= SOUNDS_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(current_sound_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(current_sound_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC_SET_X
                    && event.motion.x <= MUSIC_SET_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC_SET_Y
                    && event.motion.y <= MUSIC_SET_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(current_music_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(current_music_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC_X
                    && event.motion.x <= MUSIC_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC_Y
                    && event.motion.y <= MUSIC_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music_button, 255, 255, 255);
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
}

