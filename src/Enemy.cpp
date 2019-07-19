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
    unsigned int currentNode = 0;
    Aspen::Graphics::Animation *forward;
    Aspen::Graphics::Animation *backwards;
    Aspen::Graphics::Animation *death;
    float arrayX[20] = {40.0f, 82.0f, 118.0f, 172.0f, 728.0f, 801.0f, 1036.0f, 1090.0f, 1117.0f, 1078.0f, 966.0f, 916.0f, 873.0f, 780.0f, 665.0f, 640.0f, 540.0f, 255.0f, 191.0f, -35.0f};
    float arrayY[20] = {356.0f, 405.0f, 531.0f, 568.0f, 568.0f, 512.0f, 507.0f, 478.0f, 409.0f, 314.0f, 282.0f, 230.0f, 117.0f, 57.0f, 137.0f, 239.0f, 289.0f, 289.0f, 235.0f, 235.0f};

public:
    enemy(Object *parent = nullptr, std::string name = "enemy") : Aspen::Object::Object(parent, name)
    {
        CreateChild<Aspen::Transform::Transform>();
        forward = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/forward-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatFwd"), 1.0f / 10.0f, this, "Animation");
        backwards = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/backwards-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatBckd"), 1.0f / 10.0f, this, "Animation");
        death = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/death-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatDeath"), 1.0f / 10.0f, this, "Animation");
        AddChild(forward);
        AddChild(backwards);
        AddChild(death);
        backwards->Deactivate();
        death->Deactivate();
        GetTransform()->SetScale(.25, .25);
        GetTransform()->SetPosition(-170, 1437);
        CreateChild<Aspen::Physics::Rigidbody>();
        CreateChild<Aspen::Physics::CircleCollider>()->SetRadius(16);
    }

    void OnUpdate()
    {
        if (currentNode < sizeof(arrayY) / sizeof(float) && currentNode < sizeof(arrayX) / sizeof(float))
        {
            float dy = arrayY[currentNode] - GetTransform()->GetYPosition();
            float dx = arrayX[currentNode] - GetTransform()->GetXPosition();

            GetRigidbody()->SetCartesianVelocity(dx, dy);
            GetRigidbody()->SetVelocityStrength(.6 * 6);
            // if (GetTransform()->GetXPosition() == arrayX[currentNode] && GetTransform()->GetYPosition() == arrayY[currentNode])
            float r = 20;
            Aspen::Log::Debug("%f, %f", dx, dy);
            if (dy * dy + dx * dx < r * r)
            {
                Aspen::Log::Debug("Close!");
                if (currentNode == 8)
                {
                    forward->Deactivate();
                    backwards->Activate();
                }
                currentNode++;
            }
        }
        else
            GetRigidbody()->SetVelocityStrength(0);
    }
};