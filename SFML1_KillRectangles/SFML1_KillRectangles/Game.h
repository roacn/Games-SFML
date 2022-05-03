#ifndef GAME_H
#define GAME_H
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
//using namespace sf;

class Game
{
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode VideoMode;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //Text
    sf::Text uiText;

    //Game logic
    bool endGame;
    unsigned int points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    unsigned int maxEnemies;
    bool mouseHeld;
    
    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private functions
    void initVariables();
    void initFont();
    void initText();
    void initWindow();
    void initEnemies();
public:
    //Constructors /Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const;
    const bool getEndGame() const;

    //Functions
    void spawnEnemy();
    void pollEvents();

    void updateText();
    void updateMousePositions();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

};
#endif

