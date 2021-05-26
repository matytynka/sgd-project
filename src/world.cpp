#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <SDL2/SDL_image.h>

const int BLOCKSIZE = 50;

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
    World () {
    }

    World(SDL_Renderer * renderer) {
        this->renderer = renderer;
        this->renderX = 0;
        this->renderY = 0;
    }

    void renderWorld() {
        grassBlock = IMG_Load("grass-block.png");
        grassBlockTexture = SDL_CreateTextureFromSurface(renderer, grassBlock);
        int sizeY = map.size();
        int sizeX = map.at(0).size();
        for(int mapY = 0; mapY < sizeY; mapY++) {
            for(int mapX = 0; mapX < sizeX; mapX++) {
                SDL_Rect blockRect = {mapX * BLOCKSIZE + renderX, mapY * BLOCKSIZE + renderY, BLOCKSIZE, BLOCKSIZE};
                Block blockId = map.at(mapY).at(mapX);
                switch(blockId) {
                    case 0:
                    break;
                    case 1:
                    SDL_RenderCopy(renderer, grassBlockTexture, NULL, &blockRect);
                    break;
                }
            }
        }
    }

    void levelLoad(const char *path) {
        inFile.open(path);
        Block block;
        std::vector<Block> row;
        int blockId;
        std::string line;
        while(getline(inFile, line)) {
            std::istringstream ss(line);
            while(ss >> blockId) {
                if(blockId == 1) row.push_back(GRASS);
                if(blockId == 0) row.push_back(NOTHING);
            }
            map.push_back(row);
            row.clear();
        }
        inFile.close();
    }

    /*SDL_Rect upperLeftBlock(int x, int y){
        x = (pigDestination.x - (pigDestination.x % BLOCKSIZE)) / BLOCKSIZE
        y = (pigDestination.y - (pigDestination.y % BLOCKSIZE)) / BLOCKSIZE
    };*/

};