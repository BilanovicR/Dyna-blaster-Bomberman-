#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


class Tile {
public:
    Tile(SDL_Renderer * renderer, string tilePath, int tileId, bool walkable, bool destroyable);

    string tilePath;
    int tileId;
    bool walkable;
    bool destroyable;
    SDL_Rect *rect = new SDL_Rect();
    SDL_Texture *texture;


    void drawTile(SDL_Renderer *renderer, int id, int destX, int destY);
};


#endif // TILE_H_INCLUDED
