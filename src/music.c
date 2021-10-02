#include <../inc/header.h>

void music (SDL_Event event,SDL_Renderer *renderer, bool running){

    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/textures/background/bg1.png");
    SDL_Texture* music_title = IMG_LoadTexture(renderer, "./resource/textures/background/music_title.png");
    SDL_Texture* back_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/back_button.png");
    SDL_Texture* music1_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music1.png");
    SDL_Texture* music2_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music2.png");
    SDL_Texture* music3_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music3.png");
    SDL_Texture* music4_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music4.png");
    SDL_Texture* music5_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music5.png");
    SDL_Texture* music6_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music6.png");
    SDL_Texture* music7_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music7.png");
    SDL_Texture* music8_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music8.png");
    SDL_Texture* music9_button = IMG_LoadTexture(renderer, "./resource/textures/buttons/music9.png");

    SDL_Rect music_title_rect = {MUSIC_TITLE_X, MUSIC_TITLE_Y, MUSIC_TITLE_SIZE_X, MUSIC_TITLE_SIZE_Y};
    SDL_Rect back_rect = {BACK_X, BACK_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music1_rect = {MUSIC1_X, MUSIC1_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music2_rect = {MUSIC2_X, MUSIC2_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music3_rect = {MUSIC3_X, MUSIC3_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music4_rect = {MUSIC4_X, MUSIC4_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music5_rect = {MUSIC5_X, MUSIC5_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music6_rect = {MUSIC6_X, MUSIC6_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music7_rect = {MUSIC7_X, MUSIC7_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music8_rect = {MUSIC8_X, MUSIC8_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};
    SDL_Rect music9_rect = {MUSIC9_X, MUSIC9_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};

    Mix_Music *music1 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Music *music2 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music3 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music4 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music5 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
   
    Mix_Music *music6 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music7 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music8 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Music *music9 = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    Mix_Chunk *CLICK = Mix_LoadWAV("music/klik.wav");

    while (running)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, music_title, NULL, &music_title_rect);
        SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
        
        SDL_RenderCopy(renderer, music1_button, NULL, &music1_rect);
        SDL_RenderCopy(renderer, music2_button, NULL, &music2_rect);
        SDL_RenderCopy(renderer, music3_button, NULL, &music3_rect);
        SDL_RenderCopy(renderer, music4_button, NULL, &music4_rect);
        SDL_RenderCopy(renderer, music5_button, NULL, &music5_rect);
        SDL_RenderCopy(renderer, music6_button, NULL, &music6_rect);
        SDL_RenderCopy(renderer, music7_button, NULL, &music7_rect);
        SDL_RenderCopy(renderer, music8_button, NULL, &music8_rect);
        SDL_RenderCopy(renderer, music9_button, NULL, &music9_rect);

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
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC1_X
                    && event.button.x <= MUSIC1_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC1_Y
                    && event.button.y <= MUSIC1_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music1 = Mix_LoadMUS("./resource/music/1.mp3");
                            Mix_PlayMusic(music1, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC2_X
                    && event.button.x <= MUSIC2_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC2_Y
                    && event.button.y <= MUSIC2_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music2 = Mix_LoadMUS("./resource/music/2.mp3");
                            Mix_PlayMusic(music2, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC3_X
                    && event.button.x <= MUSIC3_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC3_Y
                    && event.button.y <= MUSIC3_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music3 = Mix_LoadMUS("./resource/music/3.mp3");
                            Mix_PlayMusic(music3, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC4_X
                    && event.button.x <= MUSIC4_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC4_Y
                    && event.button.y <= MUSIC4_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music4 = Mix_LoadMUS("./resource/music/4.wav");
                            Mix_PlayMusic(music4, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC5_X
                    && event.button.x <= MUSIC5_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC5_Y
                    && event.button.y <= MUSIC5_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music5 = Mix_LoadMUS("./resource/music/5.mp3");
                            Mix_PlayMusic(music5, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC6_X
                    && event.button.x <= MUSIC6_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC6_Y
                    && event.button.y <= MUSIC6_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music6 = Mix_LoadMUS("./resource/music/6.mp3");
                            Mix_PlayMusic(music6, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC7_X
                    && event.button.x <= MUSIC7_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC7_Y
                    && event.button.y <= MUSIC7_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music7 = Mix_LoadMUS("./resource/music/7.mp3");
                            Mix_PlayMusic(music7, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC8_X
                    && event.button.x <= MUSIC8_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC8_Y
                    && event.button.y <= MUSIC8_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music8 = Mix_LoadMUS("./resource/music/8.wav");
                            Mix_PlayMusic(music8, -1);
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= MUSIC9_X
                    && event.button.x <= MUSIC9_X + BUTTON_SIZE_X
                    && event.button.y >= MUSIC9_Y
                    && event.button.y <= MUSIC9_Y + BUTTON_SIZE_Y) {
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_Delay(250);
                        if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
                            music9 = Mix_LoadMUS("./resource/music/9.mp3");
                            Mix_PlayMusic(music9, -1);
                        }
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
                    if (event.motion.x >= MUSIC1_X
                    && event.motion.x <= MUSIC1_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC1_Y
                    && event.motion.y <= MUSIC1_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music1_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music1_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC2_X
                    && event.motion.x <= MUSIC2_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC2_Y
                    && event.motion.y <= MUSIC2_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music2_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music2_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC3_X
                    && event.motion.x <= MUSIC3_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC3_Y
                    && event.motion.y <= MUSIC3_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music3_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music3_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC4_X
                    && event.motion.x <= MUSIC4_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC4_Y
                    && event.motion.y <= MUSIC4_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music4_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music4_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC5_X
                    && event.motion.x <= MUSIC5_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC5_Y
                    && event.motion.y <= MUSIC5_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music5_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music5_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC6_X
                    && event.motion.x <= MUSIC6_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC6_Y
                    && event.motion.y <= MUSIC6_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music6_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music6_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC7_X
                    && event.motion.x <= MUSIC7_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC7_Y
                    && event.motion.y <= MUSIC7_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music7_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music7_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC8_X
                    && event.motion.x <= MUSIC8_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC8_Y
                    && event.motion.y <= MUSIC8_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music8_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music8_button, 255, 255, 255);
                    if (event.motion.x >= MUSIC9_X
                    && event.motion.x <= MUSIC9_X + BUTTON_SIZE_X
                    && event.motion.y >= MUSIC9_Y
                    && event.motion.y <= MUSIC9_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(music9_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(music9_button, 255, 255, 255);
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
}

