#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>

#include "Tile.h"

using namespace std;

class Level
{
public:
    Level(string levelPath, SDL_Renderer *renderer);
    string levelPath;
    void draw(SDL_Renderer *renderer);
    virtual ~Level();
    vector<Tile*> tiles;
    vector<vector<Tile*>> tileset;
    SDL_Renderer *renderer;

};

#endif // LEVEL_H_INCLUDED
