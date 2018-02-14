#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <vector>
#include "Sprite.h"

using namespace std;

enum LifeState {alive, dying, dead, win};//moguca stanja za svaki AS
class AnimatedSprite : public Sprite {
public:
    uint32_t frameSkip = 4;

    AnimatedSprite(const string& imagePath, int frameWidth,
                   int frameHeight,SDL_Renderer * const renderer);
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(int dx, int dy);
    virtual bool checkCollision(SDL_Rect r);
    virtual ~AnimatedSprite();
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

protected:
    uint32_t frameCount = 0;
    uint32_t currentFrame = 0;
    int life = 60;//brojac koji menja iz stanja dying u dead, kako bi se pravilno iscrtao AS
};

#endif // ANIMATEDSPRITE_H_INCLUDED
