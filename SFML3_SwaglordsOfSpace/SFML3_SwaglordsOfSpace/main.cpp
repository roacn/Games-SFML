#include <iostream>
#include <ctime>
#include "Game.h"

//using namespace sf;

int main()
{
    //Iniialize random seed
    srand(static_cast<unsigned>(time(0)));

    //Init Game engine
    Game game;

    //Game loop
    game.run();

    //End of application
    return 0;
}