#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>

#include "Tileset.h"

using namespace std;

typedef pair<char, SDL_Rect*> Tile;

class Level {
    public:
        Level(const string &path, SDL_Renderer *renderer);
        void draw(SDL_Renderer *renderer);
        virtual ~Level();
    protected:
        vector<vector<Tile*> > tiles;
        string tilesetPath;
        Tileset *tileset;
        SDL_Renderer *renderer;

    friend ifstream &operator>>(ifstream &is, Level &level);
};

#endif // LEVEL_H_INCLUDED
