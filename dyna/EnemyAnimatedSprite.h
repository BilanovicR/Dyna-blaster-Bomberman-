#ifndef BAT_H_INCLUDED
#define BAT_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "AnimatedSprite.h"
#include "Level.h"
#include "Bomb.h"


//Enumeracija dozvoljenih stanja.
enum EnemyState {moveUp, moveLeft, moveDown, moveRight};

class EnemyAnimatedSprite : public AnimatedSprite {
public:
    EnemyAnimatedSprite(SDL_Renderer *renderer, uint32_t frameSkip);
    EnemyState randomEnemyState(int i);//Metoda za prelazak na sledece stanje.
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(Level *l, vector<Bomb*> b, int dx, int dy);
    virtual ~EnemyAnimatedSprite();
    virtual bool canImove(Level *level,vector<Bomb*> b, int dX, int dY);//provera da li se enemy moze kretati po Tile-ovima i da li nema bombi da novoj poziciji
    virtual bool checkBombCollision(vector<Bomb*> bombs);//

    uint32_t frameSkip = 0;
    int moved = 0;
    EnemyState currentEnemyState;
    LifeState enemyLifeState;
};

#endif // BAT_H_INCLUDED
