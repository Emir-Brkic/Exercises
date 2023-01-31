//mingw32-make -f Makefile


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define HEIGHT 480
#define WITH 640

#define DIM_VET (WITH / 10)
#define PI 3.141592654

#define WHITE { 255, 255, 255, 255}


typedef struct circle {
    SDL_Point center;
    int radius;
} circle_t;

struct node_view {
    circle_t circle;
    SDL_Color color;
    SDL_Rect text_rect;
    SDL_Texture *text;
};

struct node_model {
    int data;
    struct node_t *left_c;
    struct node_t *right_c;
};

typedef struct node_controller {
    struct node_model model;
    struct node_view view;
} node_t;

void print_node_data(node_t *node);

void create_node(node_t **node, int value, TTF_Font *font, SDL_Renderer *rend);
void draw_node(SDL_Renderer *rend, node_t *node);
void draw_circle(SDL_Renderer *rend, int x, int y, int radius);
void free_draw(SDL_Renderer *rend);

SDL_Window *Inti_wind();
SDL_Renderer *Init_rend(SDL_Window *wind);
void Init_rect(struct SDL_Rect *rect);

void sdl_event_handler();
void sdl_draw_elements(SDL_Renderer *rend, node_t *root);

// I know that u shouldn't use global variable like this but it is just an exercise
bool run = true;
bool fullscreen = false;
bool sx_mouse_down = false;
bool dx_moust_down = false;


int x1_ = -1;
int y1_ = -1;
int x2_, y2_;

SDL_Rect textRect;
SDL_Texture *text;

int main(int argv, char** args) {
    SDL_Window *wind;
    SDL_Renderer *rend;

    wind = Inti_wind();
    rend = Init_rend(wind);

    TTF_Font *font = TTF_OpenFont("res/LEMONMILK-Light.otf", 20);
    if(font == NULL){
        printf("Font for the text doesn't exist!\n");
    }

    node_t *root;
    
    create_node(&root, 10, font, rend);
    //print_node_data(root);
    

    while(run)    {
        sdl_event_handler();
        sdl_draw_elements(rend,  root);
    }

    SDL_DestroyTexture(root->view.text);
    root->view.text = NULL;

    SDL_DestroyWindow(wind);
    SDL_Quit();

    free(root);

    return 0;
}

void print_node_data(node_t *node) {
    printf("Node model : \n");

    printf("\tNode value: %d\n",node->model.data);
    printf("\tNode left child: %X\n",node->model.left_c);
    printf("\tNode right child: %X\n",node->model.right_c);


    printf("Node view : \n");

    printf("\tNode circle:\n");
    printf("\t\tNode center: (%d;%d)\n",node->view.circle.center.x,
                                        node->view.circle.center.y);
    printf("\t\tNode radius: %d\n",node->view.circle.radius);

    printf("\tNode Text:\n");
    printf("\t\tText color: {%d - %d - %d - %d}\n",node->view.color.r,
                                    node->view.color.g,
                                    node->view.color.b,
                                    node->view.color.a);
    printf("\t\tText Texture: %d\n",node->view.text);
    printf("\t\tText rectangle: %d\n",node->view.text_rect);
}

void create_node(node_t **node, int value, TTF_Font *font, SDL_Renderer *rend) {

    *node = calloc(1,sizeof(node_t));
    if(node == NULL) {
        printf("Faild to allocate memory for the new node!\n");
    }

    SDL_Color white = WHITE;
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "69", white);
    if(textSurface == NULL) {
        printf("Faild to create a RenderText Solid!\n");
    }

    (*node)->view.color = white;
    (*node)->view.text = SDL_CreateTextureFromSurface(rend, textSurface);
    if((*node)->view.text == NULL) {
        printf("Faild to create a Texture From Surface!\n");
    }

    int ris = SDL_QueryTexture((*node)->view.text, NULL, 
                                    NULL, 
                                    &(*node)->view.text_rect.w, 
                                    &(*node)->view.text_rect.h);
    if(ris < 0) {
        printf("Faild to Query Texture!\n");
    }


    (*node)->model.data = 10;
    (*node)->model.left_c = NULL;
    (*node)->model.right_c = NULL; 

    
    (*node)->view.circle.radius = 30;
    (*node)->view.circle.center.x = WITH / 2;
    (*node)->view.circle.center.y = (*node)->view.circle.radius + 1;


    (*node)->view.text_rect.x = (*node)->view.circle.center.x - ((*node)->view.text_rect.w / 2);
    (*node)->view.text_rect.y = (*node)->view.circle.center.y - ((*node)->view.text_rect.h / 2);

    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}

void draw_node(SDL_Renderer *rend, node_t *node) {
    draw_circle(rend, node->view.circle.center.x,
                      node->view.circle.center.y,
                      node->view.circle.radius);
    int ris = SDL_RenderCopy(rend, node->view.text, NULL, &node->view.text_rect);
    if(ris < 0) {
        printf("Faild to render the text!\n");
    }
}

void draw_circle(SDL_Renderer *rend, int x, int y, int radius) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    for(double i = 0; i < 360; i++) {
        int point_x = x;
        int point_y = y;

        double an = 0;
        an = (i * PI) / 180;

        point_x += cos(an) * radius;
        point_y += sin(an) * radius;

        SDL_RenderDrawPoint(rend, point_x, point_y);
    }
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
    if(TTF_Init() < 0) {
        printf("Faild to initialize ttf library!\n");
    }

    return wind;
}

SDL_Renderer *Init_rend(SDL_Window *wind) {
    SDL_Renderer *rend;

    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

    return rend;
}



void sdl_draw_elements(SDL_Renderer *rend, node_t *root) {
    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    //SDL_RenderClear(rend);


    
    free_draw(rend);
    draw_node(rend, root);

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
