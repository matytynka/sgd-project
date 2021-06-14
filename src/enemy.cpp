#include <enemy.hpp>
#include <iostream>

Enemy::Enemy(){}

Enemy::Enemy(int x, int y){
    enemyDestination = {x, y, 94, 60}; //x, y, width/w, height/h
}

SDL_Rect Enemy::getEnemyDestination() {
    return enemyDestination;
}

void Enemy::move(bool leftBlocks, bool rightBlocks){
    if (rightWay) {
        enemyDestination.x++;
    }
    if(rightBlocks == true) {
        leftWay = true;
        rightWay = false;
        enemyDirection = 0;
    }
    if (leftWay) {
        enemyDestination.x--;
    }
    if(leftBlocks == true) {
        leftWay = false;
        rightWay = true;
        enemyDirection = 1;
    }
}

bool Enemy::checkHitboxWithPig(int pigTileX, int pigTileY) {
    //std::cout << "PIGX: " << pigTileX << " PIGY: " << pigTileY << " ENEMYX: " << enemyDestination.x
    if (pigTileX <= enemyDestination.x + enemyDestination.w &&
    pigTileX + PIG_WIDTH >= enemyDestination.x &&
    pigTileY <= enemyDestination.y + enemyDestination.h &&
    pigTileY + PIG_HEIGHT >= enemyDestination.y) {
        return true;
    }
    return false;
}

//jezeli pig jest w fall, podobny x do enemy, wiekszy y od enemy -> to enemy dead

void Enemy::display(SDL_Renderer* renderer){
        if(enemyDirection == 0) {
            SDL_RenderCopy(renderer, enemyLeftTexture, NULL, &enemyDestination);
        } else {
            SDL_RenderCopy(renderer, enemyRightTexture, NULL, &enemyDestination);
        }
        //std::cout << SDL_GetError() << std::endl;
}

void Enemy::textureLoad(SDL_Renderer* renderer){
    enemy = IMG_Load("enemy-right.png");
    enemyRightTexture = SDL_CreateTextureFromSurface(renderer, enemy);
    enemy = IMG_Load("enemy-left.png");
    enemyLeftTexture = SDL_CreateTextureFromSurface(renderer, enemy);
}