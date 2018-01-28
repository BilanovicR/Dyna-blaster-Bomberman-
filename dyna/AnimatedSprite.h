#ifndef ANIATEDSPRITE_H_INCLUDED
#define ANIATEDSPRITE_H_INCLUDED

#include <vector>
#include "Sprite.h"

using namespace std;

//Uvodimo nove nazive za vektor SDL_Rect objekata i
//vektor vektora SDL_Rect objekata. Na ovaj nacin se
//skracuje pisanje koda u pojednostavljuje razumevanje
//koda. Kljucnom recju typedef se ne kreira novi tip vec
//se uvodi alias za postojeci tip.
typedef vector<SDL_Rect> Frames;
typedef vector<Frames> Rows;

class AnimatedSprite : public Sprite {
    public:
        uint32_t frameSkip = 0;

        AnimatedSprite(const string& imagePath, int frameWidth,
                       int frameHeight, uint32_t frameSkip, SDL_Renderer * const renderer);
        //Dalje u klasama naslednicama je moguce redefinisati ove metode.
        virtual void draw(SDL_Renderer * const renderer);
        virtual void move(int dx, int dy);

    protected:
        Rows rows;
        uint32_t frameCount = 0;
        uint32_t currentRow = 0;
        uint32_t currentFrame = 0;
};

#endif // ANIATEDSPRITE_H_INCLUDED
