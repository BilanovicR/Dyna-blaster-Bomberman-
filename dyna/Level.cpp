#include "Level.h"

Level::Level(const string &path,  SDL_Renderer *renderer)
{
    //Nije lepo ni pametno resenje ali radi.
    //Na sledecim vezbama ce ovo biti preuredjeno.
    this->renderer = renderer;
    ifstream input(path);
    input >> (*this);
    input.close();
}

void Level::draw(SDL_Renderer *renderer)
{
    for(size_t i = 0; i < tiles.size(); i++) {
        for(size_t j = 0; j < tiles[i].size(); j++) {
            tileset->drawTile(tiles[i][j]->first, renderer, tiles[i][j]->second);
        }
    }
}

Level::~Level()
{
    //Kako da oslobodimo memoriju kolekcija?
}


ifstream &operator>>(ifstream &is, Level &level)
{
    string path;
    is >> path;

    level.tileset = new Tileset(path, level.renderer);

    size_t width;
    size_t height;
    is >> width;
    is >> height;

    char tileId;
    SDL_Rect *r;
    Tile *t;

    for(size_t i = 0; i < height; i++) {
        level.tiles.push_back(vector<Tile*>());
        for(size_t j = 0; j < width; j++) {
            is >> tileId;
            r = new SDL_Rect();
            r->x = j * level.tileset->tileW();
            r->y = i * level.tileset->tileH();
            t = new Tile(tileId, r);
            level.tiles[i].push_back(t);
        }
    }
    return is;
}
