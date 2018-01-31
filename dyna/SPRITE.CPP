#include "Sprite.h"

Sprite::Sprite(const string &imagePath, SDL_Renderer * const renderer) {
    //Ucitavanje slike.
    SDL_Surface *surface = IMG_Load(imagePath.c_str());
    //Podesavanje velicine i pozicije sprite-a.
    spriteRect.x = 0;
    spriteRect.y = 0;
    spriteRect.w = surface->w;
    spriteRect.h = surface->h;
    //Kreiranje teksture.
    spriteTexture = SDL_CreateTextureFromSurface(renderer, surface);

    //Oslobadjanje prostora koji je zauzeo SDL_Surface objekat.
    SDL_FreeSurface(surface);
}

void Sprite::draw(SDL_Renderer * const renderer) {
    //Isrtavanje teksture.
    //Posto je spriteRect objekat a SDL_RenderCopy na tom mestu
    //ocekuje pokazivac koristimo operator & - adresa od da bismo
    //dobavili adresu objekta.
    SDL_RenderCopy(renderer, spriteTexture, NULL, &spriteRect);
}

void Sprite::move(int dx, int dy) {
    spriteRect.x += dx;
    spriteRect.y += dy;
}

Sprite::~Sprite() {
    //Implementacija destrkutora. U ovom slucaju destruktor
    //oslobadja prostor koji je zauzet za teksturu.
    SDL_DestroyTexture(spriteTexture);
}
