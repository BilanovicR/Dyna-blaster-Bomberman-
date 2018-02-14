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

    bool checkWalkableTile(int xMatrix, int yMatrix);
    bool checkDestroyableTile(int xMatrix, int yMatrix);
    bool checkExitTile(SDL_Rect other);

    Level(string levelPath, SDL_Renderer *renderer);
    string levelPath;
    size_t width;
    size_t height;
    void draw(SDL_Renderer *renderer);
    virtual ~Level();
    TypesOfTiles levelTiles;//tipovi tile-a
    vector<vector<int>> levelMatrix;//matrica koja se ucita iz .txt datoteke

    SDL_Renderer *renderer;
};



#endif // LEVEL_H_INCLUDED
