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

class emptyBuild : public Aspen::Graphics::Rectangle
{
public:
    emptyBuild(Object *parent = nullptr, std::string name = "emptybuild")
    {
        GetTransform()->SetPosition(216.4, 278.53);
    }
};