//mingw32-make -f Makefile


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SDL.h>

#define HEIGHT 480
#define WITH 640

#define DIM_VET (WITH / 10)
#define PI 3.141592654

void draw_circle(SDL_Renderer *rend);
void free_draw(SDL_Renderer *rend);

SDL_Window *Inti_wind();
SDL_Renderer *Init_rend(SDL_Window *wind);
void Init_rect(struct SDL_Rect *rect);

void sdl_event_handler();
void sdl_draw_elements(SDL_Renderer *rend);

// I know that u shouldn't use global variable like this but it is just an exercise
bool run = true;
bool fullscreen = false;
bool sx_mouse_down = false;
bool dx_moust_down = false;


int x1_ = -1;
int y1_ = -1;
int x2_, y2_;

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

void draw_circle(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    /*for(double i = 0; i < 360; i++) {
        int an = (i * PI) / 180;
        SDL_RenderDrawPoint(rend,(int)cos((double)an) + 200,(int)sin((double)an) +200);
    }*/
}

void free_draw(SDL_Renderer *rend) {
    if(sx_mouse_down) {
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);


        Uint32 res;
        res = SDL_GetMouseState( &x2_, &y2_);


        if(SDL_BUTTON(res) == 8){
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderClear(rend);    
        }
        else if(x1_ == -1 && y1_ == -1) {
            SDL_RenderDrawLine(rend, x2_, y2_, x2_, y2_);
        }else {
            res = SDL_RenderDrawLine(rend, x1_, y1_, x2_, y2_);
        }
        

        x1_ = x2_;
        y1_ = y2_;
    }else {
        x1_ = -1;
        y1_ = -1;
    }
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
    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    //SDL_RenderClear(rend);


    
    free_draw(rend);
    printf("here\n");
    draw_circle(rend);
    printf("here\n");

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
            
            break;

        case SDL_MOUSEBUTTONDOWN:
            sx_mouse_down = true;
            dx_moust_down = true;

            
            break;

        case SDL_MOUSEBUTTONUP:
            sx_mouse_down = dx_moust_down = false;
            break;

        case SDL_MOUSEMOTION:
            break;

    
        default: 
            break;
        }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

}
