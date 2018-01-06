#ifndef ANIATEDSPRITE_H_INCLUDED
#define ANIATEDSPRITE_H_INCLUDED

#include <vector>
#include "Sprite.h"

using namespace std;

class AnimatedSprite : public Sprite
{
public:
    uint32_t frameSkip = 0;

    AnimatedSprite(const string& imagePath, int frameWidth,
                   int frameHeight, uint32_t frameSkip, SDL_Renderer * const renderer);
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(int dx, int dy);

protected:
    vector<SDL_Rect> frames;
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
};

#endif // ANIATEDSPRITE_H_INCLUDED
