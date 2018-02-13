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

    vector<Bomb*> bombs;
    int counter = 0;
    bool running = true;
    SDL_Event event;
    uint32_t frameStart = 0;
    uint32_t frameEnd = 0;
    while(counter < 50) {
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
                    //dyna->currentState = upState;
                    dyna->up(l);
                    break;
                case SDLK_DOWN:
                    //dyna->currentState = downState;
                    dyna->down(l);
                    break;
                case SDLK_LEFT:
                    //dyna->currentState = leftState;
                    dyna->left(l);
                    break;
                case SDLK_RIGHT:
                    //dyna->currentState = rightState;
                    dyna->right(l);
                    break;
                case SDLK_SPACE:
                    Bomb *b = new Bomb(renderer, dyna->spriteRect.x, dyna->spriteRect.y);
                    bombs.push_back(b);
                    break;
                }
                break;
            case SDL_KEYUP: // kada se otpusti dugme za kretanje dyna prelazi u stanje mirovanja
                dyna->currentState = stopState;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Iscrtavanje sprite-a.
        l->draw(renderer);
        dyna->draw(renderer);
        enemy->draw(renderer);
        enemy->move(l, bombs, 0, 0);

        if (bombs.size()!=0) {
            for (int i =0; i<bombs.size(); i++) {
                if (!bombs[i]->ticking) {
                    bombs[i]->explode(l, renderer);
                if (bombs[i]->ticking) bombs[i]->draw(renderer);
                else bombs[i]->explode(l, renderer);

                } else bombs[i]->draw(renderer);
                if (bombs[i]->expired) {
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
        if(dyna->checkCollision(enemy->spriteRect)) {
            dyna->currentState=deadState;
            cout << "game over" << endl;
            counter++;
        }
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
