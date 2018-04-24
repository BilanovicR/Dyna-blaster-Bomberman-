#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>

#include "Tile.h"

using namespace std;

typedef vector<Tile*> TypesOfTiles;


class Level {
public:

    string levelPath;
    size_t width;
    size_t height;
    TypesOfTiles levelTiles;//tipovi tile-a
    vector<vector<int>> levelMatrix;//matrica koja se ucita iz .txt datoteke
    SDL_Renderer *renderer;

    Level(string levelPath, SDL_Renderer *renderer);
    virtual ~Level();
    void draw(SDL_Renderer *renderer);
    bool checkWalkableTile(int xMatrix, int yMatrix);
    bool checkDestroyableTile(int xMatrix, int yMatrix);
    bool checkExitTile(SDL_Rect other);
};



#endif // LEVEL_H_INCLUDED
