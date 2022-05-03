#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <SFML/Graphics.hpp>
class Enemy
{
private:
    unsigned pointCount;
    sf::CircleShape shape;
    int type;
    float speed;
    float hp;
    float hpMax;
    float damage;
    int points;


    //Private functions
    void initVariales();
    void initShape();
public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    //Accessors
    const sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const float& getDamage() const;

    //Funtions
    void update();
    void render(sf::RenderTarget * target);
};
#endif
