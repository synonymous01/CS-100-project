#include "Game.h"

int main()
{
    Player pl1("Jack");
    Player pl2("Dong", 4, 5);
    Player pl3("Bump", 4, 9);

    pl1.setPos(190.0f, 400.0f);
    pl1.setSprite("samplecharacter.png");
    
    pl2.setPos(500.0f, 240.0f);
    pl2.setSprite("samplecharacter2.png");

    pl3.setPos(500.0f, 240.0f);
    pl3.setSprite("samplecharacter.png");

    Game g(pl1, pl2);
    g.run();
    
    return 0;
}