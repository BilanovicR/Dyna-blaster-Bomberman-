<<<<<<< HEAD
#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
//#include "Tile.h"
#include "Level.h"

using namespace std;

class Bomb {
public:

    Bomb(SDL_Renderer * const renderer, int x, int y);
    void draw(SDL_Renderer * const renderer);
    virtual ~Bomb();
    virtual void explode(Level *l, SDL_Renderer *renderer);

    vector<SDL_Rect> bombFrames;
    vector<SDL_Rect> fireFrames;
    vector<SDL_Rect> explosionFrames;
   SDL_Rect *leftTile = new SDL_Rect{0,0, 32, 32};
    SDL_Rect *rightTile = new SDL_Rect{0,0, 32, 32};
    SDL_Rect *upTile = new SDL_Rect{0,0, 32, 32};
    SDL_Rect *downTile = new SDL_Rect{0,0, 32, 32};
    SDL_Rect bombRect;
    SDL_Rect fireRect;
    SDL_Rect explosionRect;
    SDL_Texture *bombTexture;
    SDL_Texture *fireTexture;
    SDL_Texture *explosionTexture;
    int bombX;
    int bombY;
    int currentTileJ;
    int currentTileI;
    int countdown = 400;
    int explosion = 100;
    bool expired = false;
    bool ticking = true;
    uint32_t frameSkip = 3;
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
};

#endif // BOMB_H_INCLUDED
=======
#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "DynaAnimatedSprite.h"

using namespace std;

class Bomb {
public:

    Bomb(SDL_Renderer * const renderer, int x, int y);
    void draw(SDL_Renderer * const renderer);
    virtual ~Bomb();

    vector<SDL_Rect> bombFrames;
    vector<SDL_Rect> fireFrames;
    SDL_Rect bombRect;
    SDL_Rect fireRect;
    SDL_Texture *bombTexture;
    SDL_Texture *fireTexture;
    int bombX;
    int bombY;
    int countdown = 400;
    int explosion = 100;
    bool expired = false;
    uint32_t frameSkip = 4;
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
};

#endif // BOMB_H_INCLUDED
>>>>>>> 9f123de3eb2d7e56baa267ccc4906143a2791cb2
