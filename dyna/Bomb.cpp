#include "Bomb.h"

Bomb::Bomb(SDL_Renderer *renderer, int x, int y) {
    this->bombX = x;
    this->bombY = y;
    SDL_Surface *bombSurface = IMG_Load("resources/creatures/bomb.png");
    bombRect.x = 0;
    bombRect.y = 0;
    bombRect.w = bombSurface->w;
    bombRect.h = bombSurface->h;
    bombTexture = SDL_CreateTextureFromSurface(renderer, bombSurface);
    SDL_FreeSurface(bombSurface);
    if (!bombTexture) cout << "error loading texture" << endl;
    if (!bombSurface) cout << "error loading surface" << endl;

    for(int i = 0; i < bombRect.w / 30; i++) {
        SDL_Rect frame;
        frame.h = 30;
        frame.w = 30;
        frame.x = i*30;
        frame.y = 0;
        bombFrames.push_back(frame);
        //cout << bombFrames.size() << endl;
    };
    bombRect.w = 30;
    bombRect.h = 30;

// za eksploziju konstrukcija
    SDL_Surface *fireSurface = IMG_Load("resources/creatures/fire.png");
    fireRect.x = 0;
    fireRect.y = 0;
    fireRect.w = fireSurface->w;
    fireRect.h = fireSurface->h;
    fireTexture = SDL_CreateTextureFromSurface(renderer, fireSurface);
    SDL_FreeSurface(fireSurface);
    if (!fireTexture) cout << "error loading texture" << endl;
    if (!fireSurface) cout << "error loading surface" << endl;

    for(int i = 0; i < fireRect.w / 30; i++) {
        SDL_Rect frame;
        frame.h = 30;
        frame.w = 30;
        frame.x = i*30;
        frame.y = 0;
        fireFrames.push_back(frame);
        //cout << fireFrames.size() << endl;
    };
    fireRect.w = 30;
    fireRect.h = 30;
}


Bomb::~Bomb() {
    SDL_DestroyTexture(bombTexture);
    SDL_DestroyTexture(fireTexture);
}


void Bomb::draw(SDL_Renderer *renderer) {
    if (!expired) {
        if(countdown >= 0) {
            bombRect.x = bombX;
            bombRect.y = bombY;

            SDL_RenderCopy(renderer, bombTexture, &bombFrames[currentFrame], &bombRect);
            //cout << currentFrame << endl;
            frameCount++;
            countdown--;
            //cout<<countdown<<endl;
            if(frameCount > frameSkip) {
                currentFrame++;
                if(currentFrame >= bombFrames.size()) {
                    currentFrame = 0;
                }
                frameCount = 0;
            }

        } else {
            fireRect.x = bombX;
            fireRect.y = bombY;

            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame], &fireRect);
            //cout << currentFrame << endl;
            frameCount++;
            explosion--;
            //cout<<explosion<<endl;
            if(frameCount > frameSkip) {
                currentFrame++;
                if(currentFrame >= bombFrames.size()) {
                    currentFrame = 0;
                }
                frameCount = 0;
            };
            if (explosion<0) expired = true;
        }

        }
}
