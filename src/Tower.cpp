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

class tower : public Aspen::Object::Object
{

public:
    Aspen::Graphics::Sprite *sprite;
    tower(Object *parent = nullptr, std::string name = "tower")
    {
        GetTransform()->SetPosition(0, 0);
        GetTransform()->SetScale(0.34, 0.34);
    }
    double radius = 1;
    CreateChild<Aspen::Physics::CircleCollider>().SetRadius(radius);
    int damageDealt;

    OnCollision(Aspen::Physics::Collision c)
    {
    }
};

class ArcherTower : public tower
{

public:
    ArcherTower(Object *parent = nullptr, std::string name = "ArcherTower") : tower(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/archer.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
    }
    void ArcherPosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};

class MageTower : public tower
{
    Aspen::Graphics::Sprite *sprite;

public:
    MageTower(Object *parent = nullptr, std::string name = "MageTower") : tower(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/mage.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
    }
    void MagePosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};

class BoulderTower : public tower
{
    Aspen::Graphics::Sprite *sprite;

public:
    BoulderTower(Object *parent = nullptr, std::string name = "BoulderTower") : tower(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/boulder.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
    }
    void BoulderPosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};
