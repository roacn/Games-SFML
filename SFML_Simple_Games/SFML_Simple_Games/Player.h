#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};
class Player
{
private:
    sf::Sprite sprite;
    sf::Texture textureSheet;

    //Animation
    short animState;
    sf::IntRect currentFrame;
    sf::Clock animationTimer;
    bool animationsSwitch;

    //Physics
    sf::Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;
    float gravity;
    float velocityMaxY;

    //Private functions
    void initVaribales();
    void initTexture();
    void initSprite(float pos_x, float pos_y);
    void initAnimations();
    void initPhysics();

public:
    Player(float pos_x, float pos_y);
    virtual ~Player();

    //Accessors
    const bool& getAnimSwitch();
    const sf::Vector2f getPosition();
    const sf::FloatRect getBounds() const;
    //Modifiers
    void setPosition(const float x, const float y);
    void resetVelocityY();
    //Functions
    void resetAnimationTimer();
    void move(const float dir_x, const float dir_y);
    void updatePhysics();
    void updateMovement();
    void updateAnimations();
    void update();
    void render(sf::RenderTarget& target);
};
#endif
