#include "Enemy.h"

void Enemy::initVariales()
{
    this->pointCount = rand() % 20 + 3;
    this->type   = 0;
    this->speed = rand() % 3 + 1.f;
    this->hpMax  = static_cast<float>(this->pointCount);
    this->hp     = this->hpMax;
    this->damage = this->speed;
    this->points = static_cast<int>(this->speed);
}

void Enemy::initShape()
{
    this->shape.setRadius(rand() % 10 + 30.f);    //设置半径；
    this->shape.setPointCount(this->pointCount); //设置图形的点数，即边数；
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, 255));

}

Enemy::Enemy(float pos_x, float pos_y)
{
    this->initVariales();
    this->initShape();
    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
    return this->points;
}

const float& Enemy::getDamage() const
{
    return this->damage;
}

void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}
