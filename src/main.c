#include "../inc/header.h"

int main () {
    
    //SDL_Event event;
    bool running = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    //cursor
    SDL_Cursor* cursor;
    SDL_Surface* cursor_image;
    cursor_image = SDL_LoadBMP("./resource/textures/background/cur.bmp");
    cursor = SDL_CreateColorCursor(cursor_image, 0, 0);
    SDL_SetCursor(cursor);
    srand(time(NULL));
    //
    Mix_Music *music = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    if(SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
        music = Mix_LoadMUS("./resource/music/4.wav");
        Mix_PlayMusic(music, -1);
    }

    SDL_Window * window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    g_renderer = renderer;
    textures_init();
    FIRE = Mix_LoadWAV("./resource/music/explosion.wav");
    LAZER = Mix_LoadWAV("./resource/music/laser2.wav");
    CLICK = Mix_LoadWAV("./resource/music/klik.wav");
    menu(renderer, running);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}

