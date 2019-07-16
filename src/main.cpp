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
#include "Debug.hpp"
#include "GameState.hpp"
#include "Enemy.cpp"
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

class background : public Aspen::Graphics::Sprite
{
public:
  background(Object *parent = nullptr, std::string name = "background") : Aspen::Graphics::Sprite("./resources/background.png", parent, name)
  {
    GetTransform()->SetPosition(640, 360);
  }
};

class loadingAnimation : public Aspen::Graphics::Animation
{
public:
  loadingAnimation(Object *parent = nullptr, std::string name = "loadingAnimation") : Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/hourglass.png", 480, 480, 113, nullptr, "HourglassSpritesheet"), 1.0f / 20.0f, this, "Hourglass")
  {
    GetTransform()->SetPosition(640, 360);
  }
};

class MainMenu : public GameState
{
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::Animation *sprite;
  loadingAnimation *hg;
  enemy *bat;
  background *Background;

public:
  MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
  {
    Background = new background();
    hg = new loadingAnimation();
    bat = new enemy();

    // title = new Aspen::Graphics::UI::Text("M", "default", 64, this, "Title");
    // AddChild(title);
    // title->GetTransform()->SetPosition(438, 50);
    // title->GetTransform()->SetScale(0.8, 0.8);
    // title->CreateChild<Aspen::Physics::Rigidbody>();
    AddChild(Background);
    AddChild(hg);
    AddChild(bat);

    // AddChild(sprite);
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
    // double xv = title->GetRigidbody()->GetVelocityX();
    // double yv = title->GetRigidbody()->GetVelocityY();
    // if (Aspen::Input::KeyHeld(SDLK_w))
    // {
    //   yv += -0.5;
    // }
    // if (Aspen::Input::KeyHeld(SDLK_a))
    // {}
  }
};
int main(int argc, char **argv)
{
  Aspen::Log::Log::SetFile("./Aspen.log");

  Engine engine(Aspen::Engine::START_FLAGS::ALL ^ (Aspen::Engine::START_FLAGS::CREATE_GRAPHICS |
                                                   Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER |
                                                   Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE));
  Aspen::Graphics::Graphics *gfx = new Aspen::Graphics::Graphics(1280, 720, &engine, "Graphics 720p");

  engine.AddChild(gfx);
  gfx->CreateChild<Aspen::Debug::Debug>();
  gfx->CreateChild<Aspen::Graphics::FontCache>();
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(0);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
  //engine.FindChildOfType<GameStateManager>()->LoadState<Game>(false);

  while (engine)
    engine();
  return 0;
};