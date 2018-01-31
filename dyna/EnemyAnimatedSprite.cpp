#include "EnemyAnimatedSprite.h"

EnemyAnimatedSprite::EnemyAnimatedSprite(SDL_Renderer *renderer, uint32_t frameSkip) : AnimatedSprite("resources/creatures/enemy.png", 30, 30, renderer) {
    this->frameSkip = frameSkip;
    this->currentEnemyState = moveDown;
    spriteRect.x = 320;
    spriteRect.y = 320;
}

EnemyState EnemyAnimatedSprite::randomEnemyState(int i) {
    cout << " random state broj " << i << endl;
    switch(i) {
    case 0:
        currentEnemyState = moveUp;
        break;
    case 1:
        currentEnemyState = moveLeft;
        break;
    case 2:
        currentEnemyState = moveDown;
        break;
    case 3:
        currentEnemyState = moveRight;
        break;
    }
    return currentEnemyState;

}

void EnemyAnimatedSprite::draw(SDL_Renderer * const renderer) {

    //Iscrtavanje trenutnog frame-a.
    SDL_RenderCopy(renderer, spriteTexture, &frames[currentFrame], &spriteRect);
    //frameSkip i frameCount omogucuju da se upravlja brzinom animacije
    //bez promene broja FPS-a citave aplikacije.
    frameCount++;
    if(frameCount > frameSkip) {
        //Prelazenje na sledeci frame.
        currentFrame++;
        if(currentFrame >= 2) {
            //Kada se premasi broj frame-ova u slici, vraca se na pocetni
            //frame i prelazi se na sledeci red frame-ova u slici.
            currentFrame = 0;
        }
        frameCount = 0;
    }
}

void EnemyAnimatedSprite::move(Level *level, int dX, int dY) {


    if(currentEnemyState == moveLeft) {
        if (canImove(level, -1, 0)) AnimatedSprite::left();
    } else if(currentEnemyState == moveRight) {
        if (canImove(level, 1, 0)) AnimatedSprite::right();
    } else if(currentEnemyState == moveUp) {
        if (canImove(level, 0, -1)) AnimatedSprite::up();
    } else if(currentEnemyState == moveDown) {
        if (canImove(level, 0, 1)) AnimatedSprite::down();
    } else randomEnemyState(rand()%4);
    //Nasumicna promena stanja.
    moved += 1;
    if(moved > 32) {
        currentEnemyState = randomEnemyState(rand()%4);
        //cout << "move prosao if, novi state " << currentEnemyState << endl;
        moved = 0;
    }
}

bool EnemyAnimatedSprite::canImove(Level *level, int dX, int dY) {
    int topLeftX = spriteRect.x + dX;
    int topLeftY = spriteRect.y + dY;
    int topLeftI = topLeftY/32;
    int topLeftJ = topLeftX/32;

    int topRightX = spriteRect.x + spriteRect.w + dX;
    int topRightY = spriteRect.y + dY;
    int topRightI = topRightY/32;
    int topRightJ = topRightX/32;

    int bottomLeftX = spriteRect.x + dX;
    int bottomLeftY = spriteRect.y + spriteRect.h + dY;
    int bottomLeftI = bottomLeftY/32;
    int bottomLeftJ = bottomLeftX/32;


    int bottomRightX = spriteRect.x + spriteRect.w + dX;
    int bottomRightY = spriteRect.y + spriteRect.h + dY;
    int bottomRightI = bottomRightY/32;
    int bottomRightJ = bottomRightX/32;

    if(!(topRightX < 30 || bottomRightY < 30 || topRightX >= 352 || bottomRightY >= 352)) {

        if (level->checkWalkableTile(topLeftI, topLeftJ) && level->checkWalkableTile(bottomRightI, bottomRightJ)
                && level->checkWalkableTile(topRightI, topRightJ) && level->checkWalkableTile(bottomLeftI, bottomLeftJ)) {
            return true;
        }
    }
    return false;
}

EnemyAnimatedSprite::~EnemyAnimatedSprite() {

}

