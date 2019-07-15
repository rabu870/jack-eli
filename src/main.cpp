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

using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;

void ChangeScene(Aspen::Graphics::UI::Button *button, std::string scene, GameStateManager *gsm)
{
  gsm->SetCurrentState(scene);
}

class loadingAnimation : Aspen::Graphics::Animation
{
public:
  loadingAnimation(Object *parent = nullptr, std::string name = "loadingAnimation") : Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/hourglass.png", 480, 480, 113, nullptr, "HourglassSpritesheet"), 1.0f / 20.0f, this, "Hourglass")
  {
    GetTransform()->SetPosition(320, 220);
  }
}

class MainMenu : public GameState
{
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::Animation *sprite;

public:
  MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
  {
    // title = new Aspen::Graphics::UI::Text("M", "default", 64, this, "Title");
    // AddChild(title);
    // title->GetTransform()->SetPosition(438, 50);
    // title->GetTransform()->SetScale(0.8, 0.8);
    // title->CreateChild<Aspen::Physics::Rigidbody>();

    AddChild(sprite);
  }

  void OnUpdate()
  {
    // double xv = title->GetRigidbody()->GetVelocityX();
    // double yv = title->GetRigidbody()->GetVelocityY();
    // if (Aspen::Input::KeyHeld(SDLK_w))
    // {
    //   yv += -0.5;
    // }
    // if (Aspen::Input::KeyHeld(SDLK_a))
    // {
    //   xv += -0.5;
    // }
    // if (Aspen::Input::KeyHeld(SDLK_d))
    // {
    //   xv += 0.5;
    // }
    // if (Aspen::Input::KeyHeld(SDLK_s))
    // {
    //   yv += 0.5;
    // }
    // title->GetRigidbody()->SetCartesianVelocity(xv, yv);
  }
};

class Game : public GameState
{
};

int main(int argc, char **argv)
{
  Aspen::Log::Log::SetFile("./Aspen.log");

  Engine engine(Aspen::Engine::START_FLAGS::ALL);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(0);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
  //engine.FindChildOfType<GameStateManager>()->LoadState<Game>(false);

  while (engine)
    engine();
  return 0;
}