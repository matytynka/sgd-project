#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <SDL2/SDL_image.h>
#include <constants.h>

const int BLOCKSIZE = 64;

enum Block {
    NOTHING = 0,
    GRASS = 1
};

class World {

    private:
    int sizeX, sizeY;
    int renderX, renderY;
    SDL_Renderer* renderer;
    SDL_Surface* grassBlock;
    SDL_Texture* grassBlockTexture;
    std::vector<std::vector<Block>> map;
    std::ifstream inFile;

    public:    
    World(){}

    World(SDL_Renderer * renderer);

    void renderWorld();

    Point getRenderP();

    void levelLoad(const char *path);

    bool checkHitbox(int pigTileX, int pigTileY, int blockX, int blockY);

    bool upperBlocks(int pigX, int pigY);

    bool lowerBlocks(int pigX, int pigY);

    bool rightBlocks(int pigX, int pigY);

    bool leftBlocks(int pigX, int pigY);

    void moveCamera(int pigX, int pigY);
};