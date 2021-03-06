#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.h"
#include "AnimatedSprite.h"
#include "DynaAnimatedSprite.h"
#include "Level.h"
#include "EnemyAnimatedSprite.h"
#include "KeyEventHandler.h"
#include "Tile.h"
#include "Bomb.h"

using namespace std;

class Engine {
public:
    Engine();
    Engine(const string &gameTitle);
    void init();
    bool run();
    virtual ~Engine();
private:
    float frameRateCap = 16;
    string gameTitle;
    SDL_Window *window;
    SDL_Renderer *renderer;
    multimap<SDL_Keycode, KeyEventHandler*> observers;

};

#endif // ENGINE_H_INCLUDED
