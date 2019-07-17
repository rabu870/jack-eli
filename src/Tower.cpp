#include "Engine.hpp"
#include "Graphics.hpp"
#include "UI.hpp"
#include "Transform.hpp"
#include "Controller.hpp"
#include "Physics.hpp"
#include "Time.hpp"
#include "Log.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "GameState.hpp"
#include <iostream>

class tower : public Aspen::Graphics::Sprite
{
    void targetEnemy()
    {
        //TODO
    }
    double radius; //= TODO
    int damageDealt;
};

class ArcherTower : public Aspen::Object::Object
{
    Aspen::Graphics::Sprite *sprite;

public:
    ArcherTower(Object *parent = nullptr, std::string name = "ArcherTower") : Aspen::Object::Object(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/archer.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
        GetTransform()->SetPosition(0, 0);
    }
    void ArcherPosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};