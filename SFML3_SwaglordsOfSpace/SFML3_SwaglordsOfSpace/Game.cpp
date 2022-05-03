#include "Game.h"


//Private functions
void Game::initVariables()
{
    //Initialize pointers
    this->window = nullptr;
    //Game logic
    this->endGame = false;
}

void Game::initWindow()
{
    this->VideoMode = sf::VideoMode(800, 1200);
    this->window = new sf::RenderWindow(this->VideoMode, "Swaglords of Space", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player = new Player(200.f, this->window->getSize().y - 100.f);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
    //Load font
    if (!this->font.loadFromFile("fonts/simhei.ttf"))
    {
        std::cout << "ERROR::GAME::Failed to load font!" << "\n";
    }
    //Load text
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::Red);
    this->text.setCharacterSize(24);
    this->text.setString("Swaglords of Space");

    //GameOver
    this->gameOverText.setFont(this->font);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setCharacterSize(72);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2 - this->gameOverText.getGlobalBounds().width / 2,
        this->window->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2);

    //Init player GUI
    this->playerHpBarBack.setSize(sf::Vector2f(800.f, 5.f));   //width 800.f, height 5.f
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 100));
    this->playerHpBarBack.setPosition(sf::Vector2f(0.f, 0.f));
    this->playerHpBar.setSize(sf::Vector2f(800.f, 5.f));       //width 800.f, height 5.f
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(0.f, 0.f));
}

void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("Textures/background.jpg"))
    {
    }
    this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = spawnTimerMax;
    //this->enemy = new Enemy(20.f, 20.f);
}


//Constructors //Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initGUI();
    this->initWorld();
    this->initSystems();
    this->initPlayer();
    this->initTextures();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    //Delete textures
    for (auto& i : this->textures)
    {
        delete i.second;
    }
    //Delete bullets
    for (auto* i : this->bullets)
    {
        delete i;
    }

    //Delete enemies
    for (auto* i : this->enemies)
    {
        delete i;
    }
}


//Accessors
const bool Game::getEndGame() const
{
    return this->endGame;
}


//Functions
void Game::run()
{    
    while (this->window->isOpen())
    {
        this->updatePollEvent();
        this->update();
        this->render();
    }
}

void Game::updatePollEvent()
{
    while (this->window->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
        {
            this->window->close();
        }
        if (this->ev.KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
}

void Game::updateShip()
{
    //Move player
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->player->move(-1.f, 0.f);
    }
    //Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->player->move(1.f, 0.f);
    }
    //Up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->player->move(0.f, -1.f);
    }
    //Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->player->move(0.f, 1.f);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(
            this->textures["BULLET"], 
            this->player->getPos().x + 33.f, 
            this->player->getPos().y - 5.f, 
            0.f, 
            -1.f, 
            5.f
            )
        );
    }
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
    //Left world collision
    if (this->player->getBounds().left <= - this->player->getBounds().width / 2 - 1)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width / 2 - 1, this->player->getBounds().top);
    }
    //Right world collision
    if (this->player->getBounds().left + this->player->getBounds().width / 2 >= this->window->getSize().x)
    {
        this->player->setPosition(- this->player->getBounds().width / 2, this->player->getBounds().top);
    }
    //Bottom world collision
    if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
    //Top world collision
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }
}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto* bullet : this->bullets)
    {
        //Bullet culling (top of screen)
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height <= 0.f)
        {
            //Delete bullet
            delete bullets.at(counter);         //pair to "new" in function initTextures() upside.
            this->bullets.erase(this->bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << "\n";
        }
        ++counter;
    }

}

void Game::updateEnemies()
{   
    //Spawning
    this->spawnTimer += 0.5f;
    if (this->spawnTimer > this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(static_cast<float>(rand() % (this->window->getSize().x - 50)), -50.f));
        this->spawnTimer = 0.f;
    }
    
    //Update
    unsigned counter = 0;
    for (auto* enemy : this->enemies)
    {
        //Enemies move from top to bottom
        enemy->update();
        if (enemy->getBounds().top >= this->window->getSize().y)
        {
            //Delete enemy
            delete this->enemies.at(counter);       //pair to "new" upside
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        }
        //Enemy player collision
        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            //Delete enemy
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);       //pair to "new" upside
            this->enemies.erase(this->enemies.begin() + counter);            
            --counter;
        }
        ++counter;
    }
}

void Game::updateCombat()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        bool enemy_deleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                this->points += this->enemies[i]->getPoints();
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);
                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);                

                enemy_deleted = true;           //Switch to next circle, then i = i + 1.
            }
        }
        
    }
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "Points:" << this->points;
    this->text.setString(ss.str());

    //Update player GUI
    
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(800.f * hpPercent, 5.f));
    if (!hpPercent)
    {
        this->endGame = true;
    }
}

void Game::update()
{
    if (!this->endGame)
    {
        this->updateShip();
        this->updateBullets();
        this->player->update();
        this->updateCollision();
        this->updateEnemies();
        this->updateCombat();
        this->updateGUI();
        this->updateWorld();
    }
}

void Game::renderGUI()
{
    this->window->draw(this->text);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
    if (this->endGame)
    {
        this->window->draw(this->gameOverText);
    }
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::render()
{
    this->window->clear();

    //Draw BGP
    this->renderWorld();

    //Draw all the stuffs
    this->player->render(*this->window);
    for (auto * bullet : this->bullets)
    {
        bullet->render(this->window);
    }
    for (auto* enemy : this->enemies)
    {
        enemy->render(this->window);
    }
    this->renderGUI();
    this->window->display();
}
