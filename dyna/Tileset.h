#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Tileset {
    public:
        Tileset(const string &path, SDL_Renderer * const renderer);
        void drawTile(const char &tileId, SDL_Renderer * const renderer, SDL_Rect * const dest);
        int tileW() {return tileWidth;};
        int tileH() {return tileHeight;};
        virtual ~Tileset();
    protected:
        string tilesetPath;
        string texturePath;
        map<char, SDL_Rect*> tileset;
        SDL_Texture *texture;
        int textureWidth;
        int textureHeight;
        int tileWidth;
        int tileHeight;
    private:

    //Funkcije prijateljice ne pripadaju klasi direktno ali mogu da
    //pristupaju private atributima!
    friend ifstream &operator>>(ifstream &is, Tileset &tileset);
};

#endif // TILESET_H_INCLUDED
