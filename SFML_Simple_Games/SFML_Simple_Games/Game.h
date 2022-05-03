#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"
class Game
{
private:
    sf::RenderWindow window;
    sf::VideoMode VideoMode;
    sf::Event ev;

    Player* player;
    void initWindow();
    void initPlayer();
public:
    Game();
    virtual ~Game();

    //Functions    
    void run();
    void updatePlayer();
    void updateCollision();
    void update();
    void renderPlayer();
    void render();
};
#endif
