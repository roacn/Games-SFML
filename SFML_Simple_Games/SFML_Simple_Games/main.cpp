#include <iostream>
#include <ctime>
#include "Game.h"

int main()
{
    //Iniialize random seed
    srand(static_cast<unsigned>(time(0)));

    Game game;

    //Game loop
    game.run();


    //End of application
    return 0;
}