#include "Engine.h"

Engine::Engine()
{
    gameTitle = "Dyna Blaster";
}

Engine::Engine(const string &gameTitle): gameTitle(gameTitle)
{
}

void Engine::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 320, 320, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

bool Engine::run()
{
    //Instanciranje objekta klase AnimatedSprite.
    DynaAnimatedSprite *dyna = new DynaAnimatedSprite(renderer);
    Level *l = new Level("resources/levels/level1.txt", renderer);
    if (l == NULL) cout << "greska pri pravljenju levela" << endl ;

//    observers.insert(std::make_pair(SDLK_LEFT, new KeyEventHandler(dyna, &Sprite::left)));
//    observers.insert(std::make_pair(SDLK_RIGHT, new KeyEventHandler(dyna, &Sprite::right)));
//    observers.insert(std::make_pair(SDLK_UP, new KeyEventHandler(dyna, &Sprite::up)));
//    observers.insert(std::make_pair(SDLK_DOWN, new KeyEventHandler(dyna, &Sprite::down)));

    bool running = true;
    SDL_Event event;
    uint32_t frameStart = 0;
    uint32_t frameEnd = 0;
    while(running)
    {
        frameStart = SDL_GetTicks();
        //SDL_PollEvent vadi dogadjaje iz reda cekanja.
        //Izmedju dva ciklusa obrade dogadjaja moze se nakupiti
        //proizvoljan broj dogadjaja stoga se pomocu while petlje
        //obradjuju svi neobradjeni dogadjaji.
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                //Obrada dogadjaja se vrsi bez dodatnih uslova, odnosno
                //svi obradjivaci koji su se pertplatili na dogadjaj ce ga obraditi.
                if(observers.count(event.key.keysym.sym) > 0)
                {
                    //Pravljenje iteratora za multimapu.
                    pair<multimap<SDL_Keycode, KeyEventHandler*>::iterator, multimap<SDL_Keycode, KeyEventHandler*>::iterator> range = observers.equal_range(event.key.keysym.sym);
                    for(multimap<SDL_Keycode, KeyEventHandler*>::iterator it = range.first; it != range.second; it++)
                    {
                        it->second->execute();
                    }
                }
                //Prethodno resenje
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        dyna->currentState = upState;
                        dyna->move(l, 0, -2);
                    break;
                    case SDLK_DOWN:
                        dyna->currentState = downState;
                        dyna->move(l, 0, 2);
                    break;
                    case SDLK_LEFT:
                        dyna->currentState = leftState;
                        dyna->move(l, -2, 0);
                    break;
                    case SDLK_RIGHT:
                        dyna->currentState = rightState;
                        dyna->move(l, 2, 0);
                    break;
                }
                break;
                    case SDL_KEYUP: // kada se otpisti dugme za kretanje dyna prelazi u stanje mirovanja
                        dyna->currentState = stopState;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Iscrtavanje sprite-a.
        l->draw(renderer);
        dyna->draw(renderer);
        dyna->move(l, 0, 0);

        SDL_RenderPresent(renderer);

        frameEnd = SDL_GetTicks();

        //Ogranicavanje brzine iscrtavanja na frameRateCap FPS.
        if(frameEnd - frameStart < frameRateCap)
        {
            SDL_Delay(frameRateCap - (frameEnd - frameStart));
        }
    }
    return true;
}

Engine::~Engine()
{
    //Destruktor klase engine oslobadja sve resurse
    //koji su prethodno zauzeti.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
