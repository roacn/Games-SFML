#include "Player.h"

void Player::initVaribales()
{
    this->animState = PLAYER_ANIMATION_STATES::IDLE;

}

void Player::initTexture()
{
    if (!this->textureSheet.loadFromFile("Textures/player_sheet.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }    
}

void Player::initSprite(float pos_x, float pos_y)
{
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(0, 0, 40, 50);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.5f, 2.5f);
    this->sprite.setPosition(pos_x, pos_y);
}

void Player::initAnimations()
{
    this->animationTimer.restart();
    this->animationsSwitch = true;
}

void Player::initPhysics()
{
    this->velocityMax = 7.f;
    this->velocityMin = 1.f;
    this->acceleration = 1.3f;
    this->drag = 0.92f;
    this->gravity = 4.f;
    this->velocityMaxY = 7.f;
}

Player::Player(float pos_x, float pos_y)
{
    this->initVaribales();
    this->initTexture();
    this->initSprite(pos_x, pos_y);
    this->initAnimations();
    this->initPhysics();
}

Player::~Player()
{
}

const bool& Player::getAnimSwitch()
{
    bool anim_switch = this->animationsSwitch;
    if (this->animationsSwitch)
    {
        this->animationsSwitch = false;
    }
    return anim_switch;
}

const sf::Vector2f Player::getPosition()
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
    this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
    this->animationTimer.restart();
    this->animationsSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
    //Acceleraton
    this->velocity.x += dir_x * this->acceleration;
    //Limit velocity
    if (std::abs(this->velocity.x) >= this->velocityMax)
    {
        this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
    }
}

void Player::updatePhysics()
{
    //Gravity
    this->velocity.y += 1.0f * this->gravity;   //Gravity
    //Limit velocityY
    if (std::abs(this->velocity.y) >= this->velocityMaxY)
    {
        this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
    }
    //Deceleration
    this->velocity *= this->drag;

    //Limit deceleration
    if (std::abs(this->velocity.x) <= this->velocityMin)
    {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) <= this->velocityMin)
    {
        this->velocity.y = 0.f;
    }
    this->sprite.move(this->velocity);      //finally, move the sprite here!
}

void Player::updateMovement()
{
    this->animState = PLAYER_ANIMATION_STATES::IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))   //Left
    {
        this->move(-1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))   //Right
    {
        this->move(1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    }
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))   //Up
    //{
    //    this->sprite.move(0.f, -2.f);
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))   //Down
    //{
    //    this->sprite.move(0.f, 2.f);
    //}
}

void Player::updateAnimations()
{
    if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
    {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
        {
            this->currentFrame.top = 0;
            this->currentFrame.left += 40;
            if (this->currentFrame.left >= 160)
            {
                this->currentFrame.left = 0;
            }
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }
    else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
    {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
        {
            this->currentFrame.top = 50;
            this->currentFrame.left += 40;
            if (this->currentFrame.left >= 360)
            {
                this->currentFrame.left = 0;
            }
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
        this->sprite.setScale(2.5f, 2.5f);
        this->sprite.setOrigin(0.f, 0.f);
    }
    else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
    {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
        {
            this->currentFrame.top = 50;
            this->currentFrame.left += 40;
            if (this->currentFrame.left >= 360)
            {
                this->currentFrame.left = 0;
            }
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
        this->sprite.setScale(-2.5f, 2.5f);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.5f, 0.f);
    }
    else
    {
        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}

void Player::update()
{    
    this->updateMovement();
    this->updateAnimations();
    this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);

    //sf::CircleShape circ;
    //circ.setFillColor(sf::Color::Red);
    //circ.setRadius(5.f);
    //circ.setPosition(this->sprite.getPosition());
    //target.draw(circ);
}


