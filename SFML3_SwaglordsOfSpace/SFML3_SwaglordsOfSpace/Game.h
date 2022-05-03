#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
//using namespace sf;

/*
���ѣ�����ʹ���Ҽ������ٲ������ع� CTRL+.�����Ժ����������������
*/
class Game
{
private:
    //Variables
    bool endGame;

    //Window
    sf::RenderWindow* window;
    sf::VideoMode VideoMode;
    sf::Event ev;

    //Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    //GUI
    sf::Font font;
    sf::Text text;
    sf::Text gameOverText;
    
    //World
    sf::Texture worldBackgroundTexture;
    sf::Sprite worldBackground;

    //Systems
    unsigned points;
    
    //Player
    Player* player; //��*��

    //Player GUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack; //HpBar background

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
    Enemy* enemy;

    //Private functions
    void initVariables();
    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initSystems();
    void initPlayer();
    void initEnemies();

public:
    //Constructors //Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool getEndGame() const;

    //Functions
    void run();
    void updatePollEvent();
    void updateShip();
    void updateGUI();
    void updateWorld();
    void updateCollision();
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();
    void renderGUI();
    void renderWorld();
    void render();
};
#endif