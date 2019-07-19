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
#include "Enemy.hpp"
#include <iostream>

class tower : public Aspen::Object::Object
{
    double radius = 50;
    int damageDealt = 3;
    float attackSpeed = 1.0f / 90.0f;
    int AttackCooldown = 0;

public:
    Aspen::Graphics::Sprite *
        sprite;
    tower(Object *parent = nullptr, std::string name = "tower")
    {
        CreateChild<Aspen::Transform::Transform>();
        GetTransform()->SetPosition(0, 0);
        GetTransform()->SetScale(0.34, 0.34);
        CreateChild<Aspen::Physics::CircleCollider>()->SetRadius(radius);
    }

    void OnUpdate()
    {
        AttackCooldown += 1;
    }

    void OnCollision(Aspen::Physics::Collision c)
    {
        if (c.collider->Parent()->Name() == "enemy")
        {
            if (AttackCooldown > 1.0f / attackSpeed)
            {
                dynamic_cast<enemy *>(c.collider->Parent())->TakeDamage(damageDealt);
                Aspen::Log::Debug("Hitting! %d", dynamic_cast<enemy *>(c.collider->Parent())->health);
                AttackCooldown = 0;
            }
        }
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
