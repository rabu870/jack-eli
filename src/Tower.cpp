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
    double radius = 75;
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
        Aspen::Physics::CircleCollider *cc = CreateChild<Aspen::Physics::CircleCollider>();
        cc->SetRadius(radius);
        cc->SetTrigger(true);
        radius /= 0.34;
    }

    void OnUpdate()
    {
        AttackCooldown += 1;
        for (unsigned i = 0; i < Parent()->ChildrenCount(); ++i)
        {
            Aspen::Object::Object *s = Parent()->Children()[i];
            enemy *e = dynamic_cast<enemy *>(s);
            if (e)
            {
                float dx = e->GetTransform()->GetXPosition() - GetTransform()->GetXPosition();
                float dy = e->GetTransform()->GetYPosition() - GetTransform()->GetYPosition();
                float d = dx * dx + dy * dy;
                if (d <= radius * radius && e->health > 0)
                {
                    if (AttackCooldown > 1.0f / attackSpeed)
                    {
                        e->TakeDamage(damageDealt);
                        Aspen::Log::Debug("Hitting! %d", e->health);
                        AttackCooldown = 0;
                    }
                }
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
