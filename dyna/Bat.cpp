#include "Bat.h"

Bat::Bat(SDL_Renderer *renderer) : AnimatedSprite("resources/creatures/bat.png", 32, 32, 6, renderer)
{
    currentState = moveLeft;
    srand(time(NULL));
    AnimatedSprite::move(400, 250);
}

void Bat::setCurrentState(MoveState state)
{
    if((currentState == moveLeft)&&(state == moveDown))
    {
        currentState = moveDown;
    }
    else if((currentState == moveDown)&&(state == moveRight))
    {
        currentState = moveRight;
    }
    else if((currentState == moveRight)&&(state == moveUp))
    {
        currentState = moveUp;
    }
    else if((currentState == moveUp)&&(state == spinMove))
    {
        currentState = spinMove;
        cx = spriteRect.x;
        cy = spriteRect.y;
    }
    else if((currentState == spinMove)&&(state == moveLeft))
    {
        currentState = moveLeft;
    }
}

void Bat::nextState()
{
    //Promena stanja spram trenutnog stanja
    if(currentState == moveLeft)
    {
        currentState = moveDown;
    }
    else if(currentState == moveDown)
    {
        currentState = moveRight;
    }
    else if(currentState == moveRight)
    {
        currentState = moveUp;
    }
    else if(currentState == moveUp)
    {
        currentState = spinMove;
        cx = spriteRect.x;
        cy = spriteRect.y;
    }
    else if(currentState == spinMove)
    {
        currentState = moveLeft;
    }
}

void Bat::draw(SDL_Renderer * const renderer)
{
    //Poziv metode iz nadklase AnimatedSprite.
    AnimatedSprite::draw(renderer);
    //Podesavanje frame-a za iscrtavanje.
    currentRow = currentState;
    if(currentState == spinMove)
        currentRow = moveLeft;

}

void Bat::move(int dx, int dy)
{
    //Podesavanje kretanja spram stanja.
    if(currentState == moveLeft)
        AnimatedSprite::move(-1, 0);
    else if(currentState == moveRight)
        AnimatedSprite::move(1, 0);
    else if(currentState == moveUp)
        AnimatedSprite::move(0, -1);
    else if(currentState == moveDown)
        AnimatedSprite::move(0, 1);
    else if(currentState == spinMove)
    {
        angle += 0.05;

        spriteRect.x = (cx-100) + (int)(cos(angle)*100);
        spriteRect.y = cy + (int)(sin(angle)*100);
    }

    //Nasumicna promena stanja.
    moved += 1;
    if((moved > 50)&&(currentState != spinMove))
    {
        if(rand()%4 == 1)
            nextState();
        moved = 0;
    }
    else if((angle > 2*pi)&&(currentState == spinMove))
    {
        angle = 0;
        nextState();
    }
}

Bat::~Bat()
{

}
