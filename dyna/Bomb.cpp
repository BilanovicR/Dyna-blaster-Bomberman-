<<<<<<< HEAD
#include "Bomb.h"

Bomb::Bomb(SDL_Renderer *renderer, int x, int y) {
    this->bombX = (x/32)*32;
    this->bombY = (y/32)*32;
    SDL_Surface *bombSurface = IMG_Load("resources/creatures/bomb.png");
    bombRect.x = 0;
    bombRect.y = 0;
    bombRect.w = bombSurface->w;
    bombRect.h = bombSurface->h;
    bombTexture = SDL_CreateTextureFromSurface(renderer, bombSurface);
    SDL_FreeSurface(bombSurface);
    if (!bombTexture) cout << "error loading texture" << endl;
    if (!bombSurface) cout << "error loading surface" << endl;

    for(int i = 0; i < bombRect.w / 32; i++) {
        SDL_Rect frame;
        frame.h = 32;
        frame.w = 32;
        frame.x = i*32;
        frame.y = 0;
        bombFrames.push_back(frame);
        //cout << bombFrames.size() << endl;
    };
    bombRect.w = 32;
    bombRect.h = 32;

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

    for(int i = 0; i < fireRect.w / 32; i++) {
        SDL_Rect frame;
        frame.h = 32;
        frame.w = 32;
        frame.x = i*32;
        frame.y = 0;
        fireFrames.push_back(frame);
        //cout << fireFrames.size() << endl;
    };
    fireRect.w = 32;
    fireRect.h = 32;

    currentTileJ = bombX/32;
    currentTileI = bombY/32;

    SDL_Surface *explosionSurface = IMG_Load("resources/creatures/bombCenter.png");
    explosionRect.x = 0;
    explosionRect.y = 0;
    explosionRect.w = explosionSurface->w;
    explosionRect.h = explosionSurface->h;
    explosionTexture = SDL_CreateTextureFromSurface(renderer, explosionSurface);
    SDL_FreeSurface(explosionSurface);
    for(int i = 0; i < explosionRect.w / 32; i++) {
        SDL_Rect frame;
        frame.h = 32;
        frame.w = 32;
        frame.x = i*32;
        frame.y = 0;
        explosionFrames.push_back(frame);
    };
    explosionRect.w = 32;
    explosionRect.h = 32;
}


Bomb::~Bomb() {
    SDL_DestroyTexture(bombTexture);
    SDL_DestroyTexture(fireTexture);
}


void Bomb::draw(SDL_Renderer *renderer) {
    //cout << ticking<<endl;
    if (ticking) {
        if(countdown >= 0) {
            bombRect.x = bombX;
            bombRect.y = bombY;

            SDL_RenderCopy(renderer, bombTexture, &bombFrames[currentFrame], &bombRect);
            frameCount++;
            countdown--;
            if(frameCount > frameSkip) {
                currentFrame++;
                if(currentFrame >= bombFrames.size()) {
                    currentFrame = 0;
                }
                frameCount = 0;
            }
        } else ticking = false;
    }
}

void Bomb::explode(Level *l, SDL_Renderer *renderer) {

    if ((bombRect.y + bombRect.h > 32) && (currentTileI > 0)) {
        int tId = l->levelMatrix[currentTileI-1][currentTileJ];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI-1][currentTileJ] = 1;
            upTile->x = currentTileJ*32;
            upTile->y = (currentTileI-1)*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame], upTile);//gore
        };
    };
    if ((bombRect.x + bombRect.w < 352) && (currentTileJ < l->levelMatrix.size())) {
        int tId = l->levelMatrix[currentTileI][currentTileJ+1];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI][currentTileJ+1] = 1;
            rightTile->x = (currentTileJ+1)*32;
            rightTile->y = currentTileI*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+4],rightTile);//desno
        };
    };
    if ((bombRect.y + bombRect.h < 352) && (currentTileI < l->levelMatrix.size())) {
        int tId = l->levelMatrix[currentTileI+1][currentTileJ];
        cout<<tId <<endl;
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI+1][currentTileJ] = 1;
            downTile->x = currentTileJ*32;
            downTile->y = (currentTileI+1)*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+8], downTile);//dole
        };
    };
    if ((bombRect.x + bombRect.w > 32) && (currentTileJ > 0)) {
        int tId = l->levelMatrix[currentTileI][currentTileJ-1];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI][currentTileJ-1] = 1;
            leftTile->x = (currentTileJ-1)*32;
            leftTile->y = currentTileI*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+12], leftTile);//levo
        };
    };
    SDL_RenderCopy(renderer, explosionTexture, &explosionFrames[currentFrame], &bombRect);
    frameCount++;
    explosion--;
    if(frameCount > frameSkip) {
        currentFrame++;
        if(currentFrame >= 4) {
            currentFrame = 0;
        }
        frameCount = 0;
    };
    if (explosion<0) {
        expired = true;
        this->~Bomb();
    }
}

=======
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
>>>>>>> 9f123de3eb2d7e56baa267ccc4906143a2791cb2
