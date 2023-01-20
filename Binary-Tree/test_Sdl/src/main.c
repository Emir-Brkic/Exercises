//mingw32-make -f Makefile


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define HEIGHT 480
#define WITH 640

#define DIM_VET (WITH / 10)

SDL_Window *Inti_wind();
SDL_Renderer *Init_rend(SDL_Window *wind);
void Init_rect(struct SDL_Rect *rect);

void sdl_event_handler();
void sdl_draw_elements(SDL_Renderer *rend);




bool run = true, fullscreen = false;

int main(int argv, char** args) {
    SDL_Window *wind;
    SDL_Renderer *rend;

    wind = Inti_wind();
    rend = Init_rend(wind);
    



    while(run)    {
        sdl_event_handler();
        sdl_draw_elements(rend);
    }


    SDL_DestroyWindow(wind);
    SDL_Quit();

    return 0;
}

SDL_Window *Inti_wind() {

    SDL_Window *wind;

    wind = SDL_CreateWindow("Binary Tree", 400, 400, WITH, HEIGHT,  SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);

    SDL_Init(SDL_INIT_VIDEO);

    return wind;
}

SDL_Renderer *Init_rend(SDL_Window *wind) {
    SDL_Renderer *rend;

    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

    return rend;
}



void sdl_draw_elements(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 40,43,200,255);
    for(int i = 0; i < DIM_VET; i++) {
        SDL_RenderFillRect(rend, &re_vet[i]);
    }


    SDL_RenderPresent(rend);
    SDL_Delay(16);
}

void sdl_event_handler() {
    SDL_Event ev;

    while(SDL_PollEvent(&ev)) {
        switch (ev.type)
        {
        case SDL_QUIT:
            
            run = false;
            break;

        case SDL_KEYDOWN:

            if(ev.key.keysym.sym == SDLK_RETURN) {
                bab();
            }
            
            break;

    
        default: 
            break;
        }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

}

