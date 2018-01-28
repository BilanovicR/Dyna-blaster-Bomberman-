#include "Tileset.h"

Tileset::Tileset(const string &path, SDL_Renderer * const renderer)
{
    tilesetPath = path;

    //Nije lepo ni pametno resenje ali radi.
    //Na sledecim vezbama ce ovo biti preuredjeno.
    ifstream input(path);
    input >> (*this);
    input.close();

    SDL_Surface *surface = IMG_Load(texturePath.c_str());
    textureWidth = surface->w;
    textureHeight = surface->h;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
}

void Tileset::drawTile(const char &tileId, SDL_Renderer * const renderer, SDL_Rect * const dest)
{
    dest->w = tileWidth;
    dest->h = tileHeight;
    SDL_RenderCopy(renderer, texture, tileset[tileId], dest);
}

Tileset::~Tileset()
{
    //Kako da oslobodimo memoriju kolekcija?
}

ifstream &operator>>(ifstream &is, Tileset &tileset)
{
    string path;
    is >> path;

    size_t index = tileset.tilesetPath.find_last_of("/");
    tileset.texturePath = tileset.tilesetPath.substr(0, index) + "/" + path;

    is >> tileset.tileWidth;
    is >> tileset.tileHeight;

    SDL_Rect *r = new SDL_Rect();
    char tileId;

    while(is >> tileId >> r->x >> r->y) {
        r->w = tileset.tileWidth;
        r->h = tileset.tileHeight;
        tileset.tileset[tileId] = r;
        r = new SDL_Rect();
    }

    return is;
}
