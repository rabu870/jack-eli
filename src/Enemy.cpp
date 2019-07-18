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
#include <math.h>

class enemy : public Aspen::Object::Object
{
    int currentNode = 0;
    float arrayX[1] = {100.0f};
    float arrayY[1] = {100.0f};
    Aspen::Graphics::Animation *anim;

public:
    enemy(Object *parent = nullptr, std::string name = "enemy") : Aspen::Object::Object(parent, name)
    {
        CreateChild<Aspen::Transform::Transform>();
        anim = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/Bat_sprites.png", 16, 24, 15, nullptr, "BatSpriteSheet"), 1.0f / 10.0f, this, "Animation");
        AddChild(anim);
        GetTransform()->SetScale(1, 1);
        GetTransform()->SetPosition(400, 400);
        CreateChild<Aspen::Physics::Rigidbody>();
        CreateChild<Aspen::Physics::CircleCollider>()->SetRadius(16);
    }

    void OnUpdate()
    {
        if (currentNode < sizeof(arrayY) / sizeof(float) && currentNode < sizeof(arrayX) / sizeof(float))
        {
            float dy = arrayY[currentNode] - GetTransform()->GetYPosition();
            float dx = arrayX[currentNode] - GetTransform()->GetXPosition();

            GetRigidbody()->SetVelocity(1, std::atan(dy / dx) + M_PI);
            // if (GetTransform()->GetXPosition() == arrayX[currentNode] && GetTransform()->GetYPosition() == arrayY[currentNode])
            if (pow(GetTransform()->GetXPosition() - arrayX[currentNode], 2) + pow(GetTransform()->GetYPosition() - arrayY[currentNode], 2) < 1000)
            {
                currentNode++;
            }
        }
        else
            GetRigidbody()->SetVelocityStrength(0);
    }
};