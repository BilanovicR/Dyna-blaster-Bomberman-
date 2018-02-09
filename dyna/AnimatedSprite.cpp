#include "AnimatedSprite.h"

//Konstruktor klase AnimatedSprite poziva konstruktor
//nadklase String.
AnimatedSprite::AnimatedSprite(const string &imagePath,
                               int frameWidth,
                               int frameHeight,
                               SDL_Renderer * const renderer) :
    Sprite(imagePath, renderer) {
    for(int i = 0; i < spriteRect.w / frameWidth; i++) {
        SDL_Rect frame;
        frame.h = frameHeight;
        frame.w = frameWidth;
        frame.x = i*frameWidth;
        frame.y = 0;
        frames.push_back(frame);
    };

    //Podesavanje sirine i visine sprite-a.
    spriteRect.w = frameWidth;
    spriteRect.h = frameHeight;
}

void AnimatedSprite::draw(SDL_Renderer * const renderer) {

}

void AnimatedSprite::move(int dx, int dy) {
    //Poziv metode move iz nadklase Sprite.
    Sprite::move(dx, dy);
}
