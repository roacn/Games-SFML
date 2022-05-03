#include "Game.h"
#include "Player.h"
#include "SwagBall.h"

//Private functions
void Game::initVariables()
{
    //Initialize pointers
    this->window = nullptr;
    //Game logic
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 10;
    this->points = 0;
}

void Game::initWindow()
{
    this->VideoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->VideoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFont()
{
    if (!this->font.loadFromFile("fonts/simhei.ttf"))
    {
    }
}

void Game::initText()
{
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::Red);
    this->guiText.setCharacterSize(20);
    this->guiText.setString("test");

    //End game text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(sf::Vector2f(250, 200));
    this->endGameText.setString("GAME OVER");
}


//Constructors //Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

Game::~Game()
{
    delete window;
}


//Accessors
const bool& Game::running() const
{
    return this->window->isOpen() /*&& this->endGame == false*/;
}
const bool& Game::getEndGame() const
{
    return this->endGame;
}

//Functions
void Game::pollEvents()
{
    while (this->window->pollEvent(this->sfmlEvent))
    {
        switch (this->sfmlEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}

const int Game::randomizeBallType()
{
    int type = SwagBallTypes::DEFAULT;
    int randValue = rand() % 100 + 1;
    if (randValue > 60 && randValue <= 80)
    {
        type = SwagBallTypes::DAMAGING;
    }
    else if (randValue > 80 && randValue <= 100)
    {
        type = SwagBallTypes::HEALING;
    }
    return type;
}

void Game::spawnSwagBalls()
{
    //Timer
    if (this->spawnTimer < this->spawnTimerMax)
    {
        this->spawnTimer += 1.f;
    }
    else
    {
        if (this->swagBalls.size() < this->maxSwagBalls)
        {
            this->swagBalls.push_back(SwagBall(*this->window, randomizeBallType()));
            this->spawnTimer = 0.f;
        }
    }
}

void Game::updateCollision()
{
    //Check the collision
    for (size_t i = 0; i < this->swagBalls.size(); i++)
    {
        //Two globalbounds check their intersects.
        if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
        {
            //
            switch (this->swagBalls[i].getType())
            {
            case SwagBallTypes::DEFAULT:
                this->points++;
                break;
            case SwagBallTypes::DAMAGING:
                this->player.takeDamage(1);
                break;
            case SwagBallTypes::HEALING:
                this->player.gainHealth(1);
                break;
            case SwagBallTypes::NROFTYPES:
                this->points += 5;
                break;
            default:
                break;
            }

            //Add points
            this->points++;

            //Remove the ball
            this->swagBalls.erase(this->swagBalls.begin() + i);            
        }
    }
}

void Game::updateGui()
{
    std::stringstream ss;
    ss << " - Points:" << this->points << "\n"
        << " - Health:" << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
    this->guiText.setString(ss.str());
}

void Game::updatePlayer()
{
    this->player.update(this->window);
    if (this->player.getHp() <= 0)
    {
        this->endGame = true;
    }
}

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::update()
{
    this->pollEvents();
    if (this->endGame == false)
    {
        this->spawnSwagBalls();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
    else
    {

    }
}

void Game::render()
{
    /*
    void sf::RenderTarget::clear(const Color & 	color = Color(0, 0, 0, 255)	)
    */
    this->window->clear();
    for (auto& i : this->swagBalls)
    {
        i.render(this->window);
    }
    this->player.render(this->window);
    this->renderGui(this->window);

    if (this->endGame == true)
    {
        this->window->draw(this->endGameText);
    }
    this->window->display();
}
