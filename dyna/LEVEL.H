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
    //friend class AnimatedSprite;
    //friend class Tile;
    bool checkWalkableTile(int xMatrix, int yMatrix);

    Level(string levelPath, SDL_Renderer *renderer);
    string levelPath;
    size_t width;
    size_t height;
    void draw(SDL_Renderer *renderer);
    virtual ~Level();
    TypesOfTiles levelTiles;
    vector<vector<int>> levelMatrix;

    SDL_Renderer *renderer;
    //Tile* getTile(int x, int y);

};



#endif // LEVEL_H_INCLUDED
