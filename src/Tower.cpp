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
        GetTransform()->SetScale(0.34, 0.34);
    }
    void ArcherPosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};

class MageTower : public Aspen::Object::Object
{
    Aspen::Graphics::Sprite *sprite;

public:
    MageTower(Object *parent = nullptr, std::string name = "MageTower") : Aspen::Object::Object(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/mage.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
        GetTransform()->SetPosition(0, 0);
        GetTransform()->SetScale(0.34, 0.34);
    }
    void MagePosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};

class BoulderTower : public Aspen::Object::Object
{
    Aspen::Graphics::Sprite *sprite;

public:
    BoulderTower(Object *parent = nullptr, std::string name = "BoulderTower") : Aspen::Object::Object(parent, name)
    {
        sprite = new Aspen::Graphics::Sprite("./resources/towers/boulder.png", nullptr, "Name");
        AddChild(sprite);
        CreateChild<Aspen::Transform::Transform>();
        GetTransform()->SetPosition(0, 0);
        GetTransform()->SetScale(0.34, 0.34);
    }
    void BoulderPosition(double xpos, double ypos)
    {
        GetTransform()->SetPosition(xpos, ypos);
    }
};

bool defTower(int key_num, int key_letter, int num, bool isTower[])
{
    if (Aspen::Input::KeyHeld(key_letter) && Aspen::Input::KeyPressed(key_num) && !isTower[num])
    {
        return true;
    }
    else
    {
        return false;
    }
}