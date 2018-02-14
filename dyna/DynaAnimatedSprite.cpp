#include "DynaAnimatedSprite.h"

DynaAnimatedSprite::DynaAnimatedSprite(
    SDL_Renderer * const renderer)
    : AnimatedSprite("resources/creatures/9.png", 30, 30, renderer) {
    currentState = stopState;//default vrednost
    lifeState = alive;
}

void DynaAnimatedSprite::draw(SDL_Renderer * const renderer) {
    currentStateFrames.clear();
    if (lifeState == alive) {
        if (currentState == stopState) {
            currentStateFrames.push_back(frames[0]);
            currentStateFrames.push_back(frames[0]);
        } else if (currentState == downState) {
            currentStateFrames.push_back(frames[1]);
            currentStateFrames.push_back(frames[2]);
        } else if (currentState == leftState) {
            currentStateFrames.push_back(frames[6]);
            currentStateFrames.push_back(frames[7]);
            currentStateFrames.push_back(frames[8]);
        } else if (currentState == rightState) {
            currentStateFrames.push_back(frames[3]);
            currentStateFrames.push_back(frames[4]);
            currentStateFrames.push_back(frames[5]);
        } else if (currentState == upState) {
            currentStateFrames.push_back(frames[9]);
            currentStateFrames.push_back(frames[10]);
            currentStateFrames.push_back(frames[11]);
        }
    } else if (lifeState == dying) {
        currentStateFrames.push_back(frames[12]);
        currentStateFrames.push_back(frames[13]);
        currentStateFrames.push_back(frames[14]);
        currentStateFrames.push_back(frames[15]);
        currentStateFrames.push_back(frames[16]);
        currentStateFrames.push_back(frames[17]);
        currentStateFrames.push_back(frames[18]);
        currentStateFrames.push_back(frames[19]);
        life--;//pri svakom ulasku u dying stanje brojac se smanjuje
    } else if (lifeState == win) {
        currentStateFrames.push_back(frames[0]);
        currentStateFrames.push_back(frames[1]);
        currentStateFrames.push_back(frames[3]);
        currentStateFrames.push_back(frames[6]);
        currentStateFrames.push_back(frames[9]);
        currentStateFrames.push_back(frames[20]);
        currentStateFrames.push_back(frames[21]);
    };

    SDL_RenderCopy(renderer, spriteTexture, &currentStateFrames[currentFrame], &spriteRect);
    frameCount++;
    if(frameCount > frameSkip) {
        currentFrame++;
        if(currentFrame >= currentStateFrames.size()) {
            //Kada se premasi broj frame-ova u slici, vraca se na pocetni
            //frame i prelazi se na sledeci red frame-ova u slici.
            currentFrame = 0;
        }
        frameCount = 0;
    };
    if (life<=0) this->lifeState = dead;//kada brojac dodje do 0 tada prelazi u stanje dead
}

void DynaAnimatedSprite::move(Level *level, int dX, int dY) {
    //kretanje samo dok je Dyna u zivotu, u stanju dying i dead nije omoguceno kretanje
    if (lifeState == alive) {

        //racunanje ivica nove pozicije Dyne
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

        // provera da ne izadje iz okvira igre
        if(!(topRightX < 30 || bottomRightY < 30 || topRightX >= 352 || bottomRightY >= 352)) {
            //provera za Tile sa svake strane da li je walkable, odnosno da li Dyna moze da se krece na novu poziciju
            if (level->checkWalkableTile(topLeftI, topLeftJ) && level->checkWalkableTile(bottomRightI, bottomRightJ)
                    && level->checkWalkableTile(topRightI, topRightJ) && level->checkWalkableTile(bottomLeftI, bottomLeftJ)) {

                if(currentState == stopState) {
                    Sprite::move(0, 0);
                } else {
                    Sprite::move(dX, dY);
                }
            }
        }
    }
}
void DynaAnimatedSprite::left(Level *l) {
    currentState = leftState;
    move(l, -2, 0);
}
void DynaAnimatedSprite::right(Level *l) {
    currentState = rightState;
    move(l, 2, 0);
}
void DynaAnimatedSprite::up(Level *l) {
    currentState = upState;
    move(l, 0, -2);
}
void DynaAnimatedSprite::down(Level *l) {
    currentState = downState;
    move(l, 0, 2);
}




