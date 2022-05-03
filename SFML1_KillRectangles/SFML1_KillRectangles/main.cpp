#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include "Game.h"
//using namespace sf;
/*
��Ҫ����2Dƽ����Ϸ����
������
1��2D
2��ƽ��
*/
int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init Game engine
    Game game;

    //Game loop
    while (game.running())
    {
        //Event polling

        //Update
        game.update();
        //Render
        game.render();
    }

    //End of application
    return 0;
}