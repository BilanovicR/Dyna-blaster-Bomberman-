#include "AnimatedSprite.h"

//Konstruktor klase AnimatedSprite poziva konstruktor
//nadklase String.
AnimatedSprite::AnimatedSprite(const string &imagePath,
                               int frameWidth,
                               int frameHeight,
                               uint32_t frameSkip,
                               SDL_Renderer * const renderer) :
                Sprite(imagePath, renderer)
{
    this->frameSkip = frameSkip;

    //Atributi texture i spriteRect inicijalizovani su u Sprite konstruktoru
    //pa ih je sada moguce koristiti u telu AnimatedSprite konstruktora.

    //Izdvajanje delova slike koji predstavljaju pojedinacne frame-ove.
    for(int i = 0; i < spriteRect.h / frameHeight; i++) {
        Frames frames;
        for(int j = 0; j < spriteRect.w / frameWidth; j++) {
            SDL_Rect frame = {j*frameWidth, i*frameHeight, frameWidth, frameHeight};
            frames.push_back(frame);
        }
        rows.push_back(frames);
    }

    //Podesavanje sirine i visine sprite-a.
    spriteRect.w = frameWidth;
    spriteRect.h = frameHeight;
}

void AnimatedSprite::draw(SDL_Renderer * const renderer)
{
    //Iscrtavanje trenutnog frame-a.
    SDL_RenderCopy(renderer, texture, &rows[currentRow][currentFrame], &spriteRect);

    //frameSkip i frameCount omogucuju da se upravlja brzinom animacije
    //bez promene broja FPS-a citave aplikacije.
    frameCount++;
    if(frameCount > frameSkip)
    {
        //Prelazenje na sledeci frame.
        currentFrame++;
        if(currentFrame >= rows[currentRow].size()) {
            //Kada se premasi broj frame-ova u slici, vraca se na pocetni
            //frame i prelazi se na sledeci red frame-ova u slici.
            currentFrame = 0;
            currentRow++;
            if(currentRow >= rows.size()) {
                //Ukoliko je premasen ukupan broj redova vraca se na pocetni red.
                currentRow = 0;
            }
        }
        frameCount = 0;
    }

}

void AnimatedSprite::move(int dx, int dy)
{
    //Poziv metode move iz nadklase Sprite.
    Sprite::move(dx, dy);
}
