#include "Level.h"

Level::Level(string path, SDL_Renderer *renderer)
{
    size_t width;
    size_t height;
    ifstream input;
    int tileId;
    Tile *t;

    levelPath = path;
    input.open(levelPath.c_str());
    input >> width;
    input >> height;

    for(size_t i = 0; i < width; i++)
    {
        tileset.push_back(vector<Tile*>());
        for(size_t j = 0; j < height; j++)
        {
            input >> tileId;
            t = new Tile(tileId, renderer);
            tileset[i].push_back(t);
        };
    }
}

void Level::draw(SDL_Renderer *renderer)
{

    for(size_t i = 0; i < tileset.size(); i++)
    {
        for(size_t j = 0; j < tileset[i].size(); j++)
        {
            SDL_Rect *dest = new SDL_Rect();
            dest->x = j*(tileset[i][j]->tileWidth);
            dest->y = i*(tileset[i][j]->tileHeight);
            dest->w = tileset[i][j]->tileWidth;
            dest->h = tileset[i][j]->tileHeight;

            tileset[i][j]->drawTile(renderer, tileset[i][j]->texture, dest);
        }
    }
}

Level::~Level()
{
    tileset.clear();
}
