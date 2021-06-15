#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <constants.h>

class Enemy {
    private:
        SDL_Surface* enemy = NULL;
        SDL_Texture* enemyLeftTexture;
        SDL_Texture* enemyRightTexture;
        SDL_Rect enemyDestination;

        int enemyDirection = 1;
        int deadTimer = 200;

        bool dead = false;
        bool leftWay = false;
        bool rightWay = true;


    public:
        Enemy();
        Enemy(int x, int y);
        SDL_Rect getEnemyDestination();
        void setDead();
        int getDeadTimer();
        void move(bool leftBlocks, bool rightBlocks);
        bool checkHitboxWithPig(int pigTileX, int pigTileY);
        void display(SDL_Renderer* renderer);
        void textureLoad(SDL_Renderer* renderer);
};