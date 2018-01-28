#ifndef KEYEVENTHANDLER_H_INCLUDED
#define KEYEVENTHANDLER_H_INCLUDED

#include <SDL2/SDL.h>
#include "Sprite.h"

//Struktura koja cuva podatke o key handler-u.
struct KeyEventHandler
{
    //Pokazivac na sprite.
    Sprite *sprite;
    SpriteFunction handler;
    KeyEventHandler(Sprite *sprite, SpriteFunction handler) : sprite(sprite), handler(handler)
    {

    }

    void execute()
    {
        //Poziv funkcije clanice handler nad objektom sprite.
        (sprite->*handler)();
    }
};

#endif // KEYEVENTHANDLER_H_INCLUDED
