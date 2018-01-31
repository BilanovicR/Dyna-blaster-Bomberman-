#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <vector>
#include "Sprite.h"

using namespace std;

enum MoveStates {leftState, rightState, upState, downState, stopState};
class AnimatedSprite : public Sprite {
public:
    uint32_t frameSkip = 4;

    AnimatedSprite(const string& imagePath, int frameWidth,
                   int frameHeight,SDL_Renderer * const renderer);
    //Dalje u klasama naslednicama je moguce redefinisati ove metode.
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(int dx, int dy);
    virtual void left() {
        move(-1, 0);
    };
    virtual void right() {
        move(1, 0);
    };
    virtual void up() {
        move(0, -1);
    };
    virtual void down() {
        move(0, 1);
    };

    MoveStates currentState;

protected:
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
};

#endif // ANIMATEDSPRITE_H_INCLUDED
