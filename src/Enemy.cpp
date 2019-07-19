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
#include <math.h>

extern int playerHealth;

enemy::enemy(Object *parent, std::string name) : Aspen::Object::Object(parent, name)
{
    CreateChild<Aspen::Transform::Transform>();
    forward = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/forward-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatFwd"), 1.0f / 10.0f, this, "Animation");
    backwards = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/backwards-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatBckd"), 1.0f / 10.0f, this, "Animation");
    death = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/bat/death-lg.png", 16 * 8, 24 * 8, 5, nullptr, "BatDeath"), 1.0f / 10.0f, this, "Animation");

    healthbar = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/healthbar.png", 256, 256, 11, nullptr, "HealthBar"), 0, this, "Animation");
    healthbar->GetTransform()->ModifyYPosition(-64);
    AddChild(healthbar);

    AddChild(forward);
    AddChild(backwards);
    AddChild(death);
    backwards->Deactivate();
    death->Deactivate();
    GetTransform()->SetScale(.25, .25);
    GetTransform()->SetPosition(-170, 1437);
    CreateChild<Aspen::Physics::Rigidbody>();
    CreateChild<Aspen::Physics::CircleCollider>()->SetRadius(16);
    changedHealth = false;
}

void enemy::OnUpdate()
{

    float hpbar = (1 - float(health) / float(maxHP)) * healthbar->GetFrameCount();
    healthbar->SetFrame(int(hpbar));
    Aspen::Log::Debug("HP Bar: %f, %d, %d", hpbar, health, maxHP);

    if (currentNode < (sizeof(arrayY) / sizeof(float)) - 1 && currentNode < (sizeof(arrayX) / sizeof(float)) - 1)
    {
        float dy = arrayY[currentNode] - GetTransform()->GetYPosition();
        float dx = arrayX[currentNode] - GetTransform()->GetXPosition();

        GetRigidbody()->SetCartesianVelocity(dx, dy);
        if (health > 0)
        {
            GetRigidbody()->SetVelocityStrength(.6 * 16);
        }
        else
        {
            GetRigidbody()->SetVelocityStrength(0);
        }
        // if (GetTransform()->GetXPosition() == arrayX[currentNode] && GetTransform()->GetYPosition() == arrayY[currentNode])
        float r = 20;
        if (dy * dy + dx * dx < r * r)
        {
            //Aspen::Log::Debug("Close!");
            if (currentNode == 8)
            {
                forward->Deactivate();
                backwards->Activate();
            }
            currentNode++;
        }
    }
    else if (currentNode < sizeof(arrayY) / sizeof(float) && currentNode < sizeof(arrayX) / sizeof(float))
    {
        float dy = arrayY[currentNode] - GetTransform()->GetYPosition();
        float dx = arrayX[currentNode] - GetTransform()->GetXPosition();

        GetRigidbody()->SetCartesianVelocity(dx, dy);

        GetRigidbody()->SetVelocityStrength(.6 * 16);

        // if (GetTransform()->GetXPosition() == arrayX[currentNode] && GetTransform()->GetYPosition() == arrayY[currentNode])
        float r = 20;
        if (dy * dy + dx * dx < r * r)
        {
            currentNode++;
        }
        if (!changedHealth)
        {
            crossed = true;
            changedHealth = true;
            --playerHealth;
            Aspen::Log::Debug("%d", playerHealth);
        }
    }
    else
    {
        End();
    }

    if (death->Active())
    {
        if (death->GetFrame() == death->GetFrameCount() - 1)
        {
            death->SetFrameDelay(0);
            deathTimer += Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::Time::Time>()->DeltaTime();
        }
        if (deathTimer > 3)
        {
            End();
        }
    }
}

void enemy::TakeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        GetRigidbody()->SetVelocityStrength(0);
        forward->Deactivate();
        backwards->Deactivate();
        death->Activate();
        //End();
    }
}