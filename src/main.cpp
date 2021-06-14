#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <world.hpp>
#include <enemy.hpp>
#include <vector>

World world;
std::vector <Enemy> bluePigs;
SDL_Renderer* renderer;
SDL_Window * window;
SDL_Surface* guineaPig = NULL;
SDL_Texture* guineaPigRightTexture;
SDL_Texture* guineaPigLeftTexture;
SDL_Event event;
SDL_Rect pigDestination;

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

    bluePigs.push_back(Enemy(921, 644));

    bluePigs.push_back(Enemy(521, 644));

    pigDestination = {70, window_height - 80, 94, 60};
    
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Window", 100, 100, window_width, window_height, 0);

    if(window == NULL){   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    guineaPig = IMG_Load("guinea-pig-right.png");
    guineaPigRightTexture = SDL_CreateTextureFromSurface(renderer, guineaPig);
    guineaPig = IMG_Load("guinea-pig-left.png");
    guineaPigLeftTexture = SDL_CreateTextureFromSurface(renderer, guineaPig);

    for(int i = 0; i < bluePigs.size(); i++) {
        bluePigs.at(i).textureLoad(renderer);
    }

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
            pigDestination.x+=2;
            pigDirection = 1;
            //printf("x: %i, y: %i ", pigDestination.x, pigDestination.y);
        }
        if (state[SDL_SCANCODE_LEFT]) {
            pigDestination.x-=2;
            pigDirection = 0;
        }
        if (state[SDL_SCANCODE_SPACE] && !jump && canJump) {
            jump = true;
            canJump = false;
        }
        /*if (state[SDL_MOUSEBUTTONDOWN]) { // przesun enemy tam gdzie klikasz
            if (event.button.button == SDL_BUTTON_LEFT){
            mx = event.button.x;
            my = event.button.y;
            enemyDestination.x = mx;
            enemyDestination.y = my;
            }
        }*/

        //przesuwanie enemy
        for(int i = 0; i < bluePigs.size(); i++) {
            SDL_Rect enemyDestination = bluePigs.at(i).getEnemyDestination();
            bluePigs.at(i).move(world.leftBlocks(enemyDestination.x, enemyDestination.y), world.rightBlocks(enemyDestination.x, enemyDestination.y));
            if (bluePigs.at(i).checkHitboxWithPig(pigDestination.x, pigDestination.y)) {
                std::cout << "dead pig" << std::endl;
            }
        }

        //hitbox swini
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

        for(int i = 0; i < bluePigs.size(); i++) {
            bluePigs.at(i).display(renderer);
        }

        SDL_RenderPresent(renderer);

    }

    SDL_FreeSurface(guineaPig);
    
    SDL_Quit(); 

    return 0;   
}