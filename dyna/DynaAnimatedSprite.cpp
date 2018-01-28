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

/*bool AnimatedSprite::checkCollision(Level *levelWithTiles, int dX, int dY) {
    int i = (spriteRect.x + dX + spriteRect.w)/32;
    int j = (spriteRect.y + dY + spriteRect.h)/32;
    int idOfNextTile = getIdFromMatrix(levelWithTiles, i, j);
    cout<<i<<endl;
    cout<<j<<endl;
}*/

void DynaAnimatedSprite::move(Level *levelWithTiles, int dX, int dY)
{
    /*int i = (spriteRect.x + dX + spriteRect.w)/32;
    int j = (spriteRect.y + dY + spriteRect.h)/32;
    int idOfNextTile = getIdFromMatrix(levelWithTiles, i, j);
    cout<<i<<endl;
    cout<<j<<endl;

    nextTile = levelWithTiles->levelTiles[idOfNextTile];
        if (nextTile->walkable == true){*/

        if(currentState == stopState) {
        Sprite::move(0, 0);
    }
    else {
        Sprite::move(dX, dY);
    }
}
