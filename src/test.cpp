#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "world.cpp"

World world;
SDL_Renderer* renderer;
SDL_Window * window;
SDL_Surface* guineaPig = NULL;
SDL_Texture* guineaPigRightTexture;
SDL_Texture* guineaPigLeftTexture;
SDL_Surface* enemy = NULL;
SDL_Texture* enemyTexture;
SDL_Event event;
SDL_Rect pigDestination;
SDL_Rect enemyDestination;
const Uint8 * state = SDL_GetKeyboardState(NULL);

int main(int argc, char* args[]){ 

    bool quit = false;
    int window_width = 1280;
    int window_height = 720;
    int mx = 0;
    int my = 0;
    int pigDirection = 1;

    bool canJump = true;
    bool jump = false;
    bool fall = false;
    float jumpVel = 0;
    float fallVel = 0;
    float gravity = 0.1f;


    pigDestination = {1, window_height - 80, 94, 60};
    enemyDestination = {1, 40, 94, 60}; //x, y, width/w, height/h
    
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Window", 100, 100, window_width, window_height, 0);

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

    world = World(renderer);
    world.levelLoad("level-1.txt");
    
    while (!quit){
        SDL_RenderClear(renderer);
        world.renderWorld();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }

        int prevX = pigDestination.x;
        int prevY = pigDestination.y;

        if (state[SDL_SCANCODE_RIGHT]) {
            //printf("Right key pressed.\n");
            pigDestination.x+=2;
            pigDirection = 1;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            //printf("Left key pressed.\n");
            pigDestination.x-=2;
            pigDirection = 0;
        }
        if (state[SDL_SCANCODE_SPACE] && !jump && canJump) {
            jump = true;
            canJump = false;
        }
        if (state[SDL_MOUSEBUTTONDOWN]) {
            if (event.button.button == SDL_BUTTON_LEFT){
            mx = event.button.x;
            my = event.button.y;
            enemyDestination.x = mx;
            enemyDestination.y = my;
            }
        }

        if(world.rightBlocks(pigDestination.x, pigDestination.y) == true || world.leftBlocks(pigDestination.x, pigDestination.y) == true) {
            pigDestination.x = prevX;
        }

        if(world.upperBlocks(pigDestination.x, pigDestination.y) == true) {
            jump = false;
            fall = true;
        }
        // jezeli pod swinia nic nie ma
        if(world.lowerBlocks(pigDestination.x, pigDestination.y) == false) {
            // ale nie jest w trakcie skoku
            if(!jump) {
                fall = true;
                jumpVel = 6;
            }
        } else {
            // jezeli pod nia coś jednak jest
            fall = false;
            canJump = true;
            fallVel = 0;
            jumpVel = 6;
        }; 

        // jezeli jest w trakcie skoku to leci do gory
        if (jump) {
            pigDestination.y -= jumpVel;
            jumpVel -= gravity;
            if(jumpVel <= 0) {
                jump = false;
                fall = true;
            }
        }

        // jezeli jest w trakcie spadania to leci w dol
        if (fall) {
            pigDestination.y += fallVel;
            fallVel += gravity;
        }

        //std::cout << "jump = " << jump << " fall = " << fall << " jumpVel = " << jumpVel << " fallVel = " << fallVel << std::endl;

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