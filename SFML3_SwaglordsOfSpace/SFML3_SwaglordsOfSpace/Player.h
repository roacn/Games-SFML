#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;
    float attackCoolDown;
    float attackCoolDownMax;

    float hpMax;
    float hp;


    //Private functions
    void initVariables();
    void initTexture();
    void initSprite(float pos_x, float pos_y);
public:
    Player(float pos_x, float pos_y);
    virtual ~Player();

    //Accesser
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const float& getHp() const;
    const float& getHpMax() const;

    //Modifiers
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);


    //Functions
    void move(const float dirX, const float dirY);
    const bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);
};
#endif