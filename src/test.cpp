#include "SDL2/SDL.h" 
#include <stdio.h>
#include "SDL2/SDL_image.h"

int main(int argc, char* args[]){ 

    SDL_Window * window;
    SDL_Renderer* renderer;
    //SDL_Surface* screenSurface = NULL;
    SDL_Surface* guineaPig = NULL;
    SDL_Texture* guineaPigRightTexture;
    SDL_Texture* guineaPigLeftTexture;
    SDL_Surface* enemy = NULL;
    SDL_Texture* enemyTexture;
    SDL_Event event;
    SDL_Rect pigDestination;
    SDL_Rect enemyDestination;
    
    const Uint8 * state = SDL_GetKeyboardState(NULL);

    bool quit = false;
    int window_width = 480;
    int window_height = 640;
    int mx = 0;
    int my = 0;
    int pigDirection = 1;

    pigDestination = {1, window_width - 80, 94, 60};
    enemyDestination = {1, 40, 94, 60}; //x, y, width, height
    enemyDestination.h = 62;
    enemyDestination.w = 94;
    
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Window", 100, 100, window_height, window_width, 0);

    if(window == NULL){   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    //screenSurface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, 0);

    guineaPig = IMG_Load("guinea-pig-right.png");
    guineaPigRightTexture = SDL_CreateTextureFromSurface(renderer, guineaPig);
    guineaPig = IMG_Load("guinea-pig-left.png");
    guineaPigLeftTexture = SDL_CreateTextureFromSurface(renderer, guineaPig);
    //SDL_FreeSurface(guineaPig);
    enemy = IMG_Load("enemy.png");
    enemyTexture = SDL_CreateTextureFromSurface(renderer, enemy);
    
    while (!quit){
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            printf("Right key pressed.\n");
            pigDestination.x++;
            pigDirection = 1;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            printf("Left key pressed.\n");
            pigDestination.x--;
            pigDirection = 0;
        }
        if (state[SDL_SCANCODE_SPACE]) {
            printf("Space key pressed.\n");
            pigDestination.y--;
        }
        if (state[SDL_MOUSEBUTTONDOWN]) {
            if (event.button.button == SDL_BUTTON_LEFT){
            mx = event.button.x;
            my = event.button.y;
            enemyDestination.x = mx;
            enemyDestination.y = my;
            //printf("Mouse pressed at: ", mx, ", ", my);
            }
        }
        //SDL_FillRect(screenSurface, NULL, 0x000000);
        //SDL_BlitSurface(enemy, NULL, screenSurface, &enemyDestination);
        //SDL_BlitSurface(guineaPig, NULL, screenSurface, &pigDestination);
        //SDL_UpdateWindowSurface(window);
        if(pigDirection == 0) {
            SDL_RenderCopy(renderer, guineaPigLeftTexture, NULL, &pigDestination);
        } else {
            SDL_RenderCopy(renderer, guineaPigRightTexture, NULL, &pigDestination);
        }
        SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyDestination);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(guineaPig);
    
    SDL_Quit(); 

    return 0;   
}