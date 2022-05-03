#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 4.f;
    this->attackCoolDownMax = 10.f;
    this->attackCoolDown = this->attackCoolDownMax;

    this->hpMax = 10.f;
    this->hp = this->hpMax;
}

void Player::initTexture()
{
    //this->texture.loadFromFile("Textures/ship.png");
    //Load a texture from file
    if (!this->texture.loadFromFile("Textures/ship.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load the texture file" << "\n";
    }
}

void Player::initSprite(float pos_x, float pos_y)
{
    //Set the texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize the sprite
    this->sprite.scale(0.1f, 0.1f);
    this->sprite.setPosition(pos_x, pos_y);
}

Player::Player(float pos_x, float pos_y)
{
    this->initVariables();
    this->initTexture();
    this->initSprite(pos_x, pos_y);
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const float& Player::getHp() const
{
    return this->hp;
}

const float& Player::getHpMax() const
{
    return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
    this->hp = hp;
}

void Player::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
    {
        this->hp = 0;
    }
}


void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
    if (this->attackCoolDown >= this->attackCoolDownMax)
    {
        this->attackCoolDown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if (this->attackCoolDown < this->attackCoolDownMax)
    {
        this->attackCoolDown += 0.5f;
    }

}

void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
