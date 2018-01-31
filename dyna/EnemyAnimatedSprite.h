#ifndef BAT_H_INCLUDED
#define BAT_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "AnimatedSprite.h"
#include "Level.h"

//constexpr double pi = atan(1)*4;
//Enumeracija dozvoljenih stanja.
enum EnemyState {moveUp, moveLeft, moveDown, moveRight};

class EnemyAnimatedSprite : public AnimatedSprite {
public:
    EnemyAnimatedSprite(SDL_Renderer *renderer, uint32_t frameSkip);
    //Metoda za postavljanje stanja,
//    void setCurrentState(EnemyState state);
    //Metoda za prelazak na sledece stanje.
    EnemyState randomEnemyState(int i);
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(Level *l, int dx, int dy);
    virtual ~EnemyAnimatedSprite();
    virtual bool canImove(Level *level, int dX, int dY);
protected:
    //double angle = 0;
    //int cx = 0;
    //int cy = 0;
    uint32_t frameSkip = 0;
    int moved = 0;
    EnemyState currentEnemyState;
};

#endif // BAT_H_INCLUDED
