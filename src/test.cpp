#include "SDL2/SDL.h" 
#include <stdio.h>

int main(int argc, char* args[]){ 

    SDL_Window * window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* guineaPig = NULL;
    SDL_Surface* enemy = NULL;
    SDL_Event event;
    SDL_Rect pigDestination;
    SDL_Rect enemyDestination;
    
    const Uint8 * state = SDL_GetKeyboardState(NULL);

    bool quit = false;
    int window_width = 480;
    int window_height = 640;
    int x = 1;
    int y = window_width - 80;
    int mx = 0;
    int my = 0;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Window", 100, 100, window_height, window_width, 0);
    
    if(window == NULL){   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);

    guineaPig = SDL_LoadBMP("guinea-pig-right.bmp");
    enemy = SDL_LoadBMP("enemy.bmp");
    
    while (!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            printf("Right key pressed.\n");
            guineaPig = SDL_LoadBMP("guinea-pig-right.bmp");
            x++;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            printf("Left key pressed.\n");
            guineaPig = SDL_LoadBMP("guinea-pig-left.bmp");
            x--;
        }
        if (state[SDL_SCANCODE_SPACE]) {
            printf("Space key pressed.\n");
            y--;
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
        pigDestination.x = x;
        pigDestination.y = y;
        SDL_FillRect(screenSurface, NULL, 0x000000);
        SDL_BlitSurface(enemy, NULL, screenSurface, &enemyDestination);
        SDL_BlitSurface(guineaPig, NULL, screenSurface, &pigDestination);
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(guineaPig);

    //SDL_Delay(3000);
    //SDL_DestroyWindow(window); 
    
    SDL_Quit(); 

    return 0;   
}