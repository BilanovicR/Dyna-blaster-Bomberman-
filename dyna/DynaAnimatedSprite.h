#ifndef DYNAANIMATEDSPRITE_H_INCLUDED
#define DYNAANIMATEDSPRITE_H_INCLUDED

#include <vector>
#include "Sprite.h"
#include "Tile.h"
#include "Level.h"
#include "AnimatedSprite.h"

using namespace std;

class DynaAnimatedSprite : public AnimatedSprite {
public:
    //int getIdFromMatrix(int iMatrix, int jMatrix);
    uint32_t frameSkip = 7;
    Tile *nextTile = NULL;

    DynaAnimatedSprite( SDL_Renderer * const renderer);
    void draw(SDL_Renderer * const renderer);
    void move(Level *l, int dx, int dy);
    virtual void left(Level *l);
    virtual void right(Level *l);
    virtual void up(Level *l);
    virtual void down(Level *l);
    //Tile getTile(int xTile, int yTile);
    //bool checkCollision(Level *levelWithTiles, int destinationX, int destinationY);

    vector<SDL_Rect> currentStateFrames;
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
};


#endif // DYNAANIMATEDSPRITE_H_INCLUDED
