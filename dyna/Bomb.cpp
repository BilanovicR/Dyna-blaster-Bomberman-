#include "Bomb.h"

Bomb::Bomb(SDL_Renderer *renderer, int x, int y) {
    this->bombX = (x/32)*32;//postavljanje bombe na osnovu koordinata Dyne pri cemu se postavlja tacno u okviru Tile-a
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
    if (ticking) {
        if(countdown >= 0) {
            bombRect.x = bombX;//iscrtavanje na osnovu koordinata gde je postavljena
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
    //iscrtavanje eksplozije i provera za Tile sa svake strane
    //ukoliko je Tile destroyable(wall) on se unistava i postavlja se grass Tile

    //Tile gore
    if ((bombRect.y + bombRect.h > 32) && (currentTileI > 0)) {//u slucaju da se bomba ne nalazi na gornjoj ivici prozora
        int tId = l->levelMatrix[currentTileI-1][currentTileJ];//pronadjem id iz matrice i proveravam da li je destroyable
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI-1][currentTileJ] = 1;//postavljam novu vrednost Tile-a da je grass(1)
            upTile->x = currentTileJ*32;//odredjujem koordinate Tile-a i prosledjujem ga kao destinaciju za renderovanje eksplozije
            upTile->y = (currentTileI-1)*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame], upTile);
        };
    };
    //Tile desno
    if ((bombRect.x + bombRect.w < 352) && (currentTileJ < l->levelMatrix.size())) {
        int tId = l->levelMatrix[currentTileI][currentTileJ+1];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI][currentTileJ+1] = 1;
            rightTile->x = (currentTileJ+1)*32;
            rightTile->y = currentTileI*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+4],rightTile);
        };
    };
    //Tile dole
    if ((bombRect.y + bombRect.h < 352) && (currentTileI < l->levelMatrix.size())) {
        int tId = l->levelMatrix[currentTileI+1][currentTileJ];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI+1][currentTileJ] = 1;
            downTile->x = currentTileJ*32;
            downTile->y = (currentTileI+1)*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+8], downTile);
        };
    };
    //Tile levo
    if ((bombRect.x + bombRect.w > 32) && (currentTileJ > 0)) {
        int tId = l->levelMatrix[currentTileI][currentTileJ-1];
        if (l->levelTiles[tId]->destroyable) {
            l->levelMatrix[currentTileI][currentTileJ-1] = 1;
            leftTile->x = (currentTileJ-1)*32;
            leftTile->y = currentTileI*32;
            SDL_RenderCopy(renderer, fireTexture, &fireFrames[currentFrame+12], leftTile);
        };
    };
    //iscrtavanje u sredini bombe koje se uvek izvrsava
    SDL_RenderCopy(renderer, explosionTexture, &explosionFrames[currentFrame], &bombRect);
    frameCount++;
    explosion--;//odbrojavanje eksplozije
    if(frameCount > frameSkip) {
        currentFrame++;
        if(currentFrame >= 4) {
            currentFrame = 0;
        }
        frameCount = 0;
    };
    if (explosion<0) {//pri odbrojavanju se postavlja vrednost na expired i brise iz memorije
        expired = true;
        this->~Bomb();
    }
}

