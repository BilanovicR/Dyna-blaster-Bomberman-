#include "Engine.h"

Engine::Engine() {
    gameTitle = "Dyna Blaster";
}

Engine::Engine(const string &gameTitle): gameTitle(gameTitle) {
}

void Engine::init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 352, 352, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

bool Engine::run() {
    //Instanciranje objekta klase AnimatedSprite.
    DynaAnimatedSprite *dyna = new DynaAnimatedSprite(renderer);
    EnemyAnimatedSprite *enemy = new EnemyAnimatedSprite(renderer, 10);
    Level *l = new Level("resources/levels/level1.txt", renderer);
    if (l == NULL) cout << "greska pri pravljenju levela" << endl ;

    vector<Bomb*> bombs; //vektor u koji se dodaju i brisu napravljene bombe
    vector<EnemyAnimatedSprite*> enemies; //vektor sa enemijima, dodaju se i brisu
    enemies.push_back(enemy);
    bool running = true;
    SDL_Event event;
    uint32_t frameStart = 0;
    uint32_t frameEnd = 0;
    while(dyna->lifeState != dead) {
        frameStart = SDL_GetTicks();
        //SDL_PollEvent vadi dogadjaje iz reda cekanja.
        //Izmedju dva ciklusa obrade dogadjaja moze se nakupiti
        //proizvoljan broj dogadjaja stoga se pomocu while petlje
        //obradjuju svi neobradjeni dogadjaji.
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_UP:
                    dyna->up(l);
                    break;
                case SDLK_DOWN:
                    dyna->down(l);
                    break;
                case SDLK_LEFT:
                    dyna->left(l);
                    break;
                case SDLK_RIGHT:
                    dyna->right(l);
                    break;
                case SDLK_SPACE://pravljenje nove bombe i dodavanje u vektor
                    Bomb *b = new Bomb(renderer, dyna->spriteRect.x, dyna->spriteRect.y);
                    bombs.push_back(b);
                    break;
                }
                break;
            case SDL_KEYUP: // kada se otpusti dugme za kretanje dyna prelazi u stanje mirovanja
                dyna->currentState = stopState;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Iscrtavanje levela.
        l->draw(renderer);
        //if (dyna->lifeState != dead)
            dyna->draw(renderer);

        if (enemies.size()!= 0) {
            for (int i = 0; i <enemies.size(); i++) {
                if (enemies[i]->enemyLifeState != dead) { //provera za svaki enemy da se iscrtava dok je u zivotu
                    enemies[i]->draw(renderer);
                    enemies[i]->move(l, bombs);
                } else if (enemies[i]->enemyLifeState == dead) { //ukoliko mu je stanje = dead onda se brise iz memorije i vektora
                    delete enemies[i];
                    enemies.erase(enemies.begin());
                    i--;
                }
            }
        };

        if (bombs.size()!=0) {
            for (int i =0; i<bombs.size(); i++) {
                if (bombs[i]->ticking) bombs[i]->draw(renderer);//svaka bomba dok otkucava se iscrtava
                else {
                    bombs[i]->explode(l, renderer); // u slucaju eksplozije provera da li je dodirnula dinu sa bilo koje strane
                    if (dyna->checkCollision(*(bombs[i]->leftTile))
                            || dyna->checkCollision(*(bombs[i]->rightTile))
                            || dyna->checkCollision(*(bombs[i]->upTile))
                            || dyna->checkCollision(*(bombs[i]->downTile))
                            || dyna->checkCollision(bombs[i]->bombRect)) {
                        dyna->lifeState=dying; //ukoliko jeste tada se menja stanje dyne u dying i odbrojava se promenljiva life
                    };
                    if (enemies.size()!= 0) {
                        for (int i = 0; i < enemies.size(); i++) {//isto provera za svaki enemy da li ga je dodirnula bomba i unistila
                            if (enemies[i]->checkCollision(*(bombs[i]->leftTile))
                                    || enemies[i]->checkCollision(*(bombs[i]->rightTile))
                                    || enemies[i]->checkCollision(*(bombs[i]->upTile))
                                    || enemies[i]->checkCollision(*(bombs[i]->downTile))
                                    || enemies[i]->checkCollision(bombs[i]->bombRect)) enemies[i]->enemyLifeState = dying;
                        }
                    }
                };

                if (bombs[i]->expired) {//ukoliko je bomba eksplodirala prelazi u stanje expired i brise se iz memorije
                    bombs.erase(bombs.begin());
                    i--;
                };
            }
        }

        SDL_RenderPresent(renderer);

        frameEnd = SDL_GetTicks();

        //Ogranicavanje brzine iscrtavanja na frameRateCap FPS.
        if(frameEnd - frameStart < frameRateCap) {
            SDL_Delay(frameRateCap - (frameEnd - frameStart));
        };
        if (enemies.size()!= 0) {
            for (int i = 0; i < enemies.size(); i++) { // za svakog enemyja iz liste proverava se sudar sa dynom
                if(dyna->checkCollision(enemies[i]->spriteRect)) {
                    dyna->lifeState=dying;
                };
            }
        };// u slucaju da su unisteni svi enemyji i dyna je na polju koje je exit, tada prelazi u win stanje i zavrsava se igrica
        if (l->checkExitTile(dyna->spriteRect) && enemies.size() == 0) dyna->lifeState = win;

    }
    return true;
}

Engine::~Engine() {
    //Destruktor klase engine oslobadja sve resurse
    //koji su prethodno zauzeti.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
