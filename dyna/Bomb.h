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
