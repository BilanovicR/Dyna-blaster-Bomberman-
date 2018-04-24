#include "EnemyAnimatedSprite.h"

EnemyAnimatedSprite::EnemyAnimatedSprite(SDL_Renderer *renderer, uint32_t frameSkip) : AnimatedSprite("resources/creatures/enemy.png", 30, 30, renderer) {
    this->frameSkip = frameSkip;
    this->currentEnemyState = moveDown;
    this->enemyLifeState = alive;
    spriteRect.x = 320;
    spriteRect.y = 320;
}

EnemyState EnemyAnimatedSprite::randomEnemyState(int i) {
    switch(i) {//dodela novog stanja na osnovu prosledjenog random broja i
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
    if (this->enemyLifeState == alive) {

        //Iscrtavanje trenutnog frame-a.
        SDL_RenderCopy(renderer, spriteTexture, &frames[currentFrame], &spriteRect);

    //frameSkip i frameCount omogucuju da se upravlja brzinom animacije
    //bez promene broja FPS-a citave aplikacije.
    frameCount++;
    if(frameCount > frameSkip) {
        //Prelazenje na sledeci frame.
        currentFrame++;
        if(currentFrame >= 2) {//frejmovi za iscrtavanje enemija dok je ziv su od 0 do 2
            currentFrame = 0;
        }
        frameCount = 0;
    }
} else if (this->enemyLifeState == dying){
    SDL_RenderCopy(renderer, spriteTexture, &frames[currentFrame], &spriteRect);

    //frameSkip i frameCount omogucuju da se upravlja brzinom animacije
    //bez promene broja FPS-a citave aplikacije.
    frameCount++;
    if(frameCount > frameSkip) {
        //Prelazenje na sledeci frame.
        currentFrame++;
        if(currentFrame >= 8) {//frejmovi za enemija kada umire su od 3.do 8.
            currentFrame = 3;
        }
        frameCount = 0;

    }life--;//odbrojavanje pri prelasku iz dying u dead stanje
    if (life <=0) this->enemyLifeState = dead;
    }
}

void EnemyAnimatedSprite::move(Level *level, vector<Bomb*> b) {
    //provera da li se na osnovu trenutnog stanja moze pomeriti na novu poziciju
    if(currentEnemyState == moveLeft) {
        if (canImove(level, b, -1, 0)) AnimatedSprite::left();
    } else if(currentEnemyState == moveRight) {
        if (canImove(level, b, 1, 0)) AnimatedSprite::right();
    } else if(currentEnemyState == moveUp) {
        if (canImove(level, b, 0, -1)) AnimatedSprite::up();
    } else if(currentEnemyState == moveDown) {
        if (canImove(level, b, 0, 1)) AnimatedSprite::down();
    } else randomEnemyState(rand()%4);//u slucaju da nije moguce kretanje dodeljuje se novo random stanje

    //Nasumicna promena stanja.
    moved += 1;
    if(moved > 31) {
        currentEnemyState = randomEnemyState(rand()%4);
        moved = 0;
    }
}

bool EnemyAnimatedSprite::canImove(Level *level,vector<Bomb*> b, int dX, int dY) {
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
    //provera da li je dozvoljeno kretanje na novu poziciju, odnosno da je nova pozicija dozvoljeni Tile i da nema bombu
        if (level->checkWalkableTile(topLeftI, topLeftJ)
            && level->checkWalkableTile(bottomRightI, bottomRightJ)
                && level->checkWalkableTile(topRightI, topRightJ)
            && level->checkWalkableTile(bottomLeftI, bottomLeftJ)
            && !checkBombCollision(b)) {
            return true;
        }
    }
    return false;
}

EnemyAnimatedSprite::~EnemyAnimatedSprite() {
       SDL_DestroyTexture(spriteTexture);


}

bool EnemyAnimatedSprite::checkBombCollision(vector<Bomb*> bombs) {//provera za svaku bombu iz vektora bombi da li se nalazi na novoj poziciji enemyja
    bool collision = false;
    for (int i=0; i<bombs.size(); i++) {
        if (AnimatedSprite::checkCollision(bombs[i]->bombRect)) collision = true;
    };
    return collision;
}

