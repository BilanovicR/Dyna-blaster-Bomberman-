#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Tile
{
public:
    Tile(int tileId, SDL_Renderer *renderer);

    string tilePath;
    int tileId;
    SDL_Rect *rect;
    int tileWidth;
    int tileHeight;
    bool walkable = false;

    SDL_Texture *texture;
    int textureWidth;
    int textureHeight;

    void drawTile(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect * destTile);
};


#endif // TILE_H_INCLUDED
