#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const string &imagePath,
                               int frameWidth,
                               int frameHeight,
                               uint32_t frameSkip,
                               SDL_Renderer * const renderer) :
    Sprite(imagePath, renderer)
{
    this->frameSkip = frameSkip;

    for(int i = 0; i < spriteRect.w / frameWidth; i++)
    {
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

void AnimatedSprite::draw(SDL_Renderer * const renderer)
{
    //Iscrtavanje trenutnog frame-a.
    SDL_RenderCopy(renderer, spriteTexture, &frames[currentFrame], &spriteRect);
    //frameSkip i frameCount omogucuju da se upravlja brzinom animacije
    //bez promene broja FPS-a citave aplikacije.
    frameCount++;
    if(frameCount > frameSkip)
    {
        //Prelazenje na sledeci frame.
        currentFrame++;
        if(currentFrame >= frames.size())
        {
            //Kada se premasi broj frame-ova u slici, vraca se na pocetni
            //frame i prelazi se na sledeci red frame-ova u slici.
            currentFrame = 0;
        }
        frameCount = 0;
    }

}

void AnimatedSprite::move(int dx, int dy)
{
     Sprite::move(dx, dy);
}
