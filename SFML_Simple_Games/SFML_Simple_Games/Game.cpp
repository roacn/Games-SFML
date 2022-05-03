#include "Game.h"


void Game::initWindow()
{
    this->VideoMode = sf::VideoMode(800, 600);
    this->window.create(this->VideoMode, "Game", sf::Style::Titlebar | sf::Style::Close); //this->window = new sf::RenderWindow(this->VideoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player = new Player(0.f, static_cast<float>(this->window.getSize().y - 150));
}

Game::Game()
{
    this->initWindow();
    this->initPlayer();
}

Game::~Game()
{
    delete this->player;
}

void Game::run()
{
    while (this->window.isOpen())
    {
        this->update();
        this->render();
    }
}

void Game::updatePlayer()
{
    this->player->update();
}

void Game::updateCollision()
{
    //Collision bottom of screen
    if (this->player->getPosition().y + this->player->getBounds().height >= this->window.getSize().y)
    {
        this->player->resetVelocityY();
        this->player->setPosition(this->player->getPosition().x,
            this->window.getSize().y - this->player->getBounds().height);
    }
}

void Game::update()
{
    //Polling window events
    while (this->window.pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
        {
            this->window.close();
        }
        else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
        {
            this->window.close();
        }
        if (this->ev.type == sf::Event::KeyReleased && 
            (this->ev.key.code == sf::Keyboard::A ||
                this->ev.key.code == sf::Keyboard::W ||
                this->ev.key.code == sf::Keyboard::S ||
                this->ev.key.code == sf::Keyboard::D))
        {
            this->player->resetAnimationTimer();
        }
    }

    this->updatePlayer();
    this->updateCollision();
}

void Game::renderPlayer()
{
    this->player->render(this->window);
}

void Game::render()
{
    this->window.clear();

    //Render game
    
    this->renderPlayer();
    this->window.display();
}