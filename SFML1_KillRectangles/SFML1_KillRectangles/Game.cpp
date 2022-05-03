#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <iostream>

//using namespace sf;
//////////////////////////////private////////////////////////////////////
//Private functions
void Game::initVariables()
{
    this->window = nullptr;
    //Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;    //���ù������ֶ�������޷���ʾ
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}
void Game::initFont()
{
    this->font.loadFromFile("fonts/simhei.ttf");
    if (!this->font.loadFromFile("fonts/simhei.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!\n";
    }
}
void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setFillColor(sf::Color::Red);
    this->uiText.setString("NONE");
}
void Game::initWindow()
{
    this->VideoMode.height = 600;
    this->VideoMode.width = 800;
    this->window = new sf::RenderWindow(this->VideoMode, "My Game!", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}
void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    //this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);
}

//////////////////////////////public////////////////////////////////////
//Constructors /Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
    this->initEnemies();
}
Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    /*
    bool 	isOpen () const
    Tell whether or not the window is open.
    */
    return this->window->isOpen();
}
const bool Game::getEndGame() const
{
    return this->endGame;
}


//Functions

//������������
void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and set their types and colors,Spawns them at random postions.
        -Sets a random position.
        -Sets a random color.
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );
    //Randomize enemy type
    int type = rand() % 5;
    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(60.f, 60.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(80.f, 80.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(120.f, 120.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(140.f, 140.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    default:
        break;
    }

    //Spawn the enemy
    this->enemies.push_back(this->enemy);

    //Remove enemies at end of screen
}
/*
bool pollEvent (Event &event)
���¼��������¼����еĶ���������У������䷵�ء�
����������������ģ����û�й�����¼�����ô�������� false ���Ҳ��޸��¼���
��ע�⣬�¼������п��ܴ��ڶ���¼��������Ӧ��ʼ����ѭ���е��ô˺�����ȷ������ÿ����������¼���
*/
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        /*
        void 	close ()
 	    Close the window and destroy all the attached resources. More...
        */
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}
void Game::updateText()
{
    std::stringstream ss;
    ss << "Points:" << this->points
        << "\tHealth:" << this->health;
    this->uiText.setString(ss.str());
}
void Game::updateMousePositions()
{
    /*
    @return void

    Updates the mouse positions:
        - Mouse position relative to window(Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);  //λ��������ת��Ϊ����
}
void Game::updateEnemies()
{
    /*
        @return void

        Updates the enemy spawn timer and spawns enemies
        when the total amount of enemies is smaller than the maximum.
        Moves the enemies downwards.
        Removes the enemies at the edge of the screen //TODO
    */
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Moving and updating enemies
    for (unsigned int i = 0; i < this->enemies.size(); i++)
    {        
        this->enemies[i].move(0.f, 2.f);

        //If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    //Check if clicked upon        
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;        
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                    {
                        this->points += 10;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                    {
                        this->points += 8;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                    {
                        this->points += 6;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                    {
                        this->points += 4;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
                    {
                        this->points += 2;
                    }
                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

//�����¼�
void Game::update()
{
    this->pollEvents();
    if (this->endGame == false)
    {
        this->updateMousePositions();
        this->updateEnemies();
        this->updateText();
    }
    //Condition end the game
    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

//��Ⱦ��Ϸ
void Game::render()
{
    /*
        @return void

        - clear old frame
        - render objects
        - display frame in window

        Render the game renders
    */
    /*
    void sf::RenderTarget::clear(const Color & 	color = Color(0, 0, 0, 255)	)	
    �õ�һ��ɫ�������Ŀ�ꡣ
    �ú���ͨ��ÿ֡����һ�Σ��������Ŀ��֮ǰ�����ݡ�
    ����
    ��ɫ	���������ȾĿ��������ɫ
    */
    this->window->clear();

    //Draw game objects

    this->renderText(*this->window);

    /*
    void 	draw (const Drawable &drawable, const RenderStates &states=RenderStates::Default)
 	���ɻ��ƶ�����Ƶ���ȾĿ�ꡣ
    ����
    �ɻ��Ƶ�	Ҫ���ƵĶ���
    ״̬	��Ⱦ״̬�����ڻ�ͼ
    //this->window->draw(this->enemy);
    */    
    this->renderEnemies(*this->window);

    /*
    void display ()
 	����Ļ����ʾ��ĿǰΪֹ����Ⱦ�����ڵ����ݡ�
    �˺���ͨ���ڵ�ǰ֡������ OpenGL ��Ⱦ��ɺ���ã��Ա�����Ļ����ʾ����
    */
    this->window->display();
}
