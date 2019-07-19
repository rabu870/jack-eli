#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include "Object.hpp"
#include "Graphics.hpp"

class enemy : public Aspen::Object::Object
{
    unsigned int currentNode = 0;
    Aspen::Graphics::Animation *forward;
    Aspen::Graphics::Animation *backwards;
    Aspen::Graphics::Animation *death;
    Aspen::Graphics::Animation *healthbar;
    float arrayX[20] = {40.0f, 82.0f, 118.0f, 172.0f, 728.0f, 801.0f, 1036.0f, 1090.0f, 1117.0f, 1078.0f, 966.0f, 916.0f, 873.0f, 780.0f, 665.0f, 640.0f, 540.0f, 255.0f, 191.0f, -35.0f};
    float arrayY[20] = {356.0f, 405.0f, 531.0f, 568.0f, 568.0f, 512.0f, 507.0f, 478.0f, 409.0f, 314.0f, 282.0f, 230.0f, 117.0f, 57.0f, 137.0f, 239.0f, 289.0f, 289.0f, 235.0f, 235.0f};

public:
    int maxHP = 100;
    int health = maxHP;
    enemy(Object *parent = nullptr, std::string name = "enemy");
    void OnUpdate();
    void TakeDamage(int damage);
};

#endif