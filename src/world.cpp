#include <world.hpp>

World::World(SDL_Renderer * renderer) {
    this->renderer = renderer;
    this->renderX = 0;
    this->renderY = 0;
}

void World::renderWorld() {
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

void World::levelLoad(const char *path) {
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

bool World::checkHitbox(int pigTileX, int pigTileY, int blockX, int blockY) {
    //printf("x1: %d, x2: %d, y1: %d, y2: %d ", pigTileX < (blockX + 1) * BLOCKSIZE, pigTileX + PIG_WIDTH > blockX * BLOCKSIZE, pigTileY < (blockY + 1) * BLOCKSIZE, pigTileY + PIG_HEIGHT > blockY * BLOCKSIZE);
    if (pigTileX <= (blockX + 1) * BLOCKSIZE &&
    pigTileX + PIG_WIDTH >= blockX * BLOCKSIZE &&
    pigTileY <= (blockY + 1) * BLOCKSIZE &&
    pigTileY + PIG_HEIGHT >= blockY * BLOCKSIZE) {
        //printf("pig %i, block %i \n", pigTileY, (blockY + 1) * BLOCKSIZE);
        return true;
    }
    return false;
}

bool World::upperBlocks(int pigX, int pigY) {
    int blockTileX = pigX  / BLOCKSIZE;
    int blockTileY = pigY / BLOCKSIZE;
    for (int i = 0; i < 2; i++) {
        if(pigY < PIG_HEIGHT) {
            break;
        }
        if(map.at(blockTileY).at(blockTileX + i) == 1) {
            if(checkHitbox(pigX, pigY, blockTileX + i, blockTileY) == true) {
                return true;
                break;
            }
        }
    }
    return false;   
};

bool World::lowerBlocks(int pigX, int pigY) {
    int blockTileX = pigX / BLOCKSIZE;
    int blockTileY = (pigY + PIG_HEIGHT) / BLOCKSIZE;
    for (int i = 0; i < 2; i++) {
        if(map.at(blockTileY).at(blockTileX + i) == 1) {
            if(checkHitbox(pigX, pigY, blockTileX + i, blockTileY) == true) {
                return true;
                break;
            }
        }
    }
    return false;   
};

bool World::rightBlocks(int pigX, int pigY) {
    int blockTileX = (pigX + PIG_WIDTH) / BLOCKSIZE;
    int blockTileY = (pigY  + (PIG_HEIGHT/2)) / BLOCKSIZE;
    for (int i = 0; i < 1; i++) {
        /*SDL_Rect rect = {blockTileX * BLOCKSIZE, blockTileY * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);*/
        if(map.at(blockTileY + i).at(blockTileX) == 1) {
            if(checkHitbox(pigX, pigY, blockTileX, blockTileY + i) == true){
                //printf("hitbox prawy ");
                return true;
                break;
            }
        }
    }
    return false;
};

bool World::leftBlocks(int pigX, int pigY) {
    int blockTileX = pigX  / BLOCKSIZE;
    int blockTileY = (pigY + (PIG_HEIGHT/2)) / BLOCKSIZE;
    for (int i = 0; i < 1; i++) {
        /*SDL_Rect rect = {blockTileX * BLOCKSIZE, blockTileY * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);*/
        if(map.at(blockTileY + i).at(blockTileX) == 1) {
            if(checkHitbox(pigX, pigY, blockTileX, blockTileY + i) == true){
                //printf("hitbox lewy ");

                return true;
                break;
            }
        }
    }
    return false;
};