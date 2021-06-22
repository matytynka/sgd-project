#include <enemy.hpp>
#include <iostream>
#include <constants.h>

Enemy::Enemy(){}

Enemy::Enemy(int x, int y){
    enemyDestination = {x, y, 94, 60}; //x, y, width/w, height/h
}

SDL_Rect Enemy::getEnemyDestination() {
    return enemyDestination;
}

void Enemy::move(bool leftBlocks, bool rightBlocks){
    if (!dead) {
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
}

bool Enemy::checkHitboxWithPig(int pigTileX, int pigTileY) {
    if (!dead) {
        //std::cout << "PIGX: " << pigTileX << " PIGY: " << pigTileY << " ENEMYX: " << enemyDestination.x
        if (pigTileX <= enemyDestination.x + enemyDestination.w &&
        pigTileX + PIG_WIDTH >= enemyDestination.x &&
        pigTileY <= enemyDestination.y + enemyDestination.h &&
        pigTileY + PIG_HEIGHT >= enemyDestination.y) {
            return true;
        }
        return false;
    }
}

void Enemy::setDead() {
    dead = true;
}

int Enemy::getDeadTimer() {
    return deadTimer;
}

void Enemy::display(SDL_Renderer* renderer, Point p){
    if(dead) {
        enemy = IMG_Load("enemy-right-dead.png");
        enemyRightTexture = SDL_CreateTextureFromSurface(renderer, enemy);
        enemy = IMG_Load("enemy-left-dead.png");
        enemyLeftTexture = SDL_CreateTextureFromSurface(renderer, enemy);
        deadTimer--;
        //std::cout << "deadtimer: " << deadTimer << std::endl;
    }

    enemyDestination.x = enemyDestination.x + p.x;
    enemyDestination.y = enemyDestination.y + p.y;

    if(enemyDirection == 0) {
        SDL_RenderCopy(renderer, enemyLeftTexture, NULL, &enemyDestination);
    } else {
        SDL_RenderCopy(renderer, enemyRightTexture, NULL, &enemyDestination);
    }

    enemyDestination.x = enemyDestination.x - p.x;
    enemyDestination.y = enemyDestination.y - p.y;
}

void Enemy::textureLoad(SDL_Renderer* renderer){
    enemy = IMG_Load("enemy-right.png");
    enemyRightTexture = SDL_CreateTextureFromSurface(renderer, enemy);
    enemy = IMG_Load("enemy-left.png");
    enemyLeftTexture = SDL_CreateTextureFromSurface(renderer, enemy);
    SDL_FreeSurface(enemy);
}