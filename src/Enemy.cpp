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

class enemy : public Aspen::Graphics::Animation
{
public:
    enemy(Object *parent = nullptr, std::string name = "enemy") : Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/sprites/Bat_sprites.png", 16, 24, 15, nullptr, "BatSpriteSheet"), 1.0f / 10.0f, parent, name)
    {
        FindChildOfType<Aspen::Graphics::UniformSpritesheet>()->GetTransform()->SetScale(2, 2);
        GetTransform()->SetPosition(500, 500);
    }
};