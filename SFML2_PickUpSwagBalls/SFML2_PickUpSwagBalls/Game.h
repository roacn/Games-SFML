#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "SwagBall.h"
//using namespace sf;

/*
提醒：可以使用右键“快速操作与重构 CTRL+.”来对函数定义进行声明；
*/
class Game
{
private:
    //Variables
    bool endGame;
    float spawnTimerMax;
    float spawnTimer;
    unsigned int maxSwagBalls;
    int points;

    //Window
    sf::RenderWindow* window;
    sf::VideoMode VideoMode;
    sf::Event sfmlEvent;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    //Font
    sf::Font font;
    //Text
    sf::Text guiText;
    sf::Text endGameText;

    //
    Player player;
    std::vector<SwagBall> swagBalls;


    //Private functions
    void initVariables();
    void initWindow();
    void initFont();
    void initText();

public:
    //Constructors //Destructors
    Game();
    ~Game();

    //Accessors
    const bool& running()    const;
    const bool& getEndGame() const;

    //Functions
    
    void pollEvents();
    const int randomizeBallType();
    void spawnSwagBalls();
    void updateCollision();
    void updateGui();
    void updatePlayer();
    void update();
    void renderGui(sf::RenderTarget* target);
    void render();


};
#endif