#include <iostream>
#include "Game.h"
#include "Player.h"
#include <ctime>
//using namespace sf;

int main()
{
    //Iniialize random seed
    srand(static_cast<unsigned>(time(0)));

    //Init Game engine
    Game game;

    //Game loop
    while (game.running())
    {
        //Update
        game.update();
        //Render
        game.render();
    }

    //End of application
    return 0;
}