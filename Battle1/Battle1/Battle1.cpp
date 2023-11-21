#include "Game.h"

int main()
{
    Player pl1("Jack");
    Player pl2("Dong");

    pl1.setPos(190.0f, 400.0f);
    pl1.setSprite("samplecharacter.png");
    
    pl2.setPos(500.0f, 240.0f);
    pl2.setSprite("samplecharacter.png");

    Game g(pl1, pl2);
    /*g.setState(State::ACTION);*/
    g.run();
    return 0;
}