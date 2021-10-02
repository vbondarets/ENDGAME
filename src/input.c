
#include "header.h"

bool is_key_pressed[4096] = {false};
bool is_button_pressed[32] = {false};
bool button_was_pressed[32] = {false};

int mousex = 0;
int mousey = 0;

void input_pool_events() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        for(int i = 0; i < 32; i++) {
            button_was_pressed[i] = false;
        }

        switch(event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym < 4096)
                    is_key_pressed[event.key.keysym.sym] = true;
            break;
            case SDL_KEYUP:
                if(event.key.keysym.sym < 4096)
                    is_key_pressed[event.key.keysym.sym] = false;
            break;
            case SDL_MOUSEBUTTONDOWN:
                is_button_pressed[event.button.button] = true;
                button_was_pressed[event.button.button] = true;
            break;

            case SDL_MOUSEBUTTONUP:
                is_button_pressed[event.button.button] = false;
            break;

            case SDL_MOUSEMOTION:
                mousex = event.motion.x;
                mousey = event.motion.y;
            break;
        }
    }
}

