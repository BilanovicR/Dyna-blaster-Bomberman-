#include "Tile.h"

Tile::Tile(SDL_Renderer * renderer, string tPath, int id, bool aWalkable, bool aDestroyable) {
    tilePath = tPath;
    tileId = id;
    walkable = aWalkable;
    destroyable = aDestroyable;

    SDL_Surface *surface = IMG_Load(tilePath.c_str());
    if (!surface) cout << "error loading surface" << endl;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) cout << "error loading texture" << endl;

    rect->h = surface->h;
    rect->w = surface->w;
    rect->x = 0;
    rect->y = 0;

    SDL_FreeSurface(surface);
}

void Tile::drawTile(SDL_Renderer *renderer, int id, int destinationJ, int destinationI) {
    //dest.x i y se izracunavaju na osnovu prosledjenih i i j iz matrice
    SDL_Rect *dest = new SDL_Rect();
    dest->x = destinationJ * rect->h;
    dest->y = destinationI * rect->w;
    dest->h = rect->h;
    dest->w = rect->w;
    SDL_RenderCopy(renderer, texture, rect, dest);
    delete dest;

}

