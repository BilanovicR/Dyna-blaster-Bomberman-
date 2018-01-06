#include "Tile.h"

Tile::Tile(int tId, SDL_Renderer *renderer)
{
    tileId = tId;
    if (tileId==0) {
            tilePath = "resources/tilesets/grass2.jpg";
            this->walkable = true;
    }
    else if (tileId==1) tilePath = "resources/tilesets/block.jpg";
    else if (tileId==2) tilePath = "resources/tilesets/wall.jpg";

    SDL_Surface *surface = IMG_Load(tilePath.c_str());
    if (!surface) cout << "greska surface"<< endl;

    textureWidth = surface->w;
    textureHeight = surface->h;
    tileHeight = textureHeight;
    tileWidth = textureWidth;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) cout << "greska texture"<< endl;
    SDL_FreeSurface(surface);

    rect = new SDL_Rect();
    rect->h = textureHeight;
    rect->w = textureWidth;
    rect->x = 0;
    rect->y = 0;

}

void Tile::drawTile(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect * destTile)
{
    SDL_RenderCopy(renderer, texture, rect, destTile);
}

