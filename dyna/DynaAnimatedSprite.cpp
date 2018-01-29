#include "DynaAnimatedSprite.h"

DynaAnimatedSprite::DynaAnimatedSprite(
                               SDL_Renderer * const renderer)
                                : AnimatedSprite("resources/creatures/dyna.png", 30, 30, renderer)
{
currentState = stopState;
}

void DynaAnimatedSprite::draw(SDL_Renderer * const renderer)
{
    currentStateFrames.clear();

    if (currentState == stopState) {
            currentStateFrames.push_back(frames[0]);
            currentStateFrames.push_back(frames[0]);
    }
    else if (currentState == downState) {
            currentStateFrames.push_back(frames[1]);
            currentStateFrames.push_back(frames[2]);
    }
    else if (currentState == leftState) {
            currentStateFrames.push_back(frames[6]);
            currentStateFrames.push_back(frames[7]);
            currentStateFrames.push_back(frames[8]);
    }
    else if (currentState == rightState) {
            currentStateFrames.push_back(frames[3]);
            currentStateFrames.push_back(frames[4]);
            currentStateFrames.push_back(frames[5]);
            }
    else if (currentState == upState) {

            currentStateFrames.push_back(frames[9]);
            currentStateFrames.push_back(frames[10]);
            currentStateFrames.push_back(frames[11]);
            };

    SDL_RenderCopy(renderer, spriteTexture, &currentStateFrames[currentFrame], &spriteRect);
    frameCount++;
    if(frameCount > frameSkip)
    {
        currentFrame++;
        if(currentFrame >= currentStateFrames.size())
        {
            //Kada se premasi broj frame-ova u slici, vraca se na pocetni
            //frame i prelazi se na sledeci red frame-ova u slici.
            currentFrame = 0;
        }
        frameCount = 0;
    }
}

//bool AnimatedSprite::checkCollision(Level *levelWithTiles, int dX, int dY) {
//
//    int i = (spriteRect.x + dX + spriteRect.w)/32;
//    int j = (spriteRect.y + dY + spriteRect.h)/32;
//    int idOfNextTile = getIdFromMatrix(levelWithTiles, i, j);
//    cout<<i<<endl;
//    cout<<j<<endl;
//
//
//
//if (spriteRect.x < tile->x + tile->w &&
//   spriteRect.x + spriteRect.w > tile->x &&
//   spriteRect.y < tile->y + tile->h &&
//   spriteRect.h + spriteRect.y > tile->y) {
//    return true;
//} else return false;
//}

void DynaAnimatedSprite::move(Level *level, int dX, int dY)
{
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

    if (level->checkWalkableTile(topLeftI, topLeftJ) && level->checkWalkableTile(bottomRightI, bottomRightJ)
    && level->checkWalkableTile(topRightI, topRightJ) && level->checkWalkableTile(bottomLeftI, bottomLeftJ)){

                if(currentState == stopState) {
                Sprite::move(0, 0);
                }
                else {
                    Sprite::move(dX, dY);
                    }
   }
}

