#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 5.f;
    this->hpMax = 10;
    this->hp = this->hpMax;

}

void Player::initShape()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

Player::Player(float x, float y)
{
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShape();
}

Player::~Player()
{

}

const sf::RectangleShape& Player::getShape() const
{
    return this->shape;
}

void Player::updateInput()
{
    //Keyboard input
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->shape.move(-this->movementSpeed, 0.f);
    }
    //Right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->shape.move(this->movementSpeed, 0.f);
    }
    //Up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->shape.move(0.f, -this->movementSpeed);
    }
    //Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->shape.move(0.f, this->movementSpeed);
    }
}

const int& Player::getHp() const
{
    return this->hp;
}

const int& Player::getHpMax() const
{
    return this->hpMax;
}
void Player::takeDamage(const int damage)
{
    if (this->hp > 0)
    {
        this->hp -= damage;
    }
    if (this->hp < 0)
    {
        this->hp = 0;
    }
}

void Player::gainHealth(const int health)
{
    if (this->hp < this->hpMax)
    {
        this->hp += health;
    }
    if (this->hp > this->hpMax)
    {
        this->hp = this->hpMax;
    }
}


void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    //Left
    if (this->shape.getGlobalBounds().left <= 0.f)
    {
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    }
    //Right
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
    {
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    //Top    
    if (this->shape.getGlobalBounds().top <= 0.f)
    {
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
    }
    //Bottom
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
    {
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
    }
}



void Player::update(const sf::RenderTarget* target)
{
    this->updateInput();
    //Window bounds collision
    this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}


