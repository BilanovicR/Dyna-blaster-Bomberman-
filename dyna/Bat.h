#ifndef BAT_H_INCLUDED
#define BAT_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "AnimatedSprite.h"

constexpr double pi = atan(1)*4;
//Enumeracija dozvoljenih stanja.
enum MoveState {moveUp, moveLeft, moveDown, moveRight, spinMove};

class Bat : public AnimatedSprite
{
public:
    Bat(SDL_Renderer *renderer);
    //Metoda za postavljanje stanja,
    void setCurrentState(MoveState state);
    //Metoda za prelazak na sledece stanje.
    void nextState();
    virtual void draw(SDL_Renderer * const renderer);
    virtual void move(int dx, int dy);
    virtual ~Bat();
protected:
    double angle = 0;
    int cx = 0;
    int cy = 0;
    int moved = 0;
    MoveState currentState;
};

#endif // BAT_H_INCLUDED
