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
#include "emptyBuild.cpp"
#include "Tower.cpp"
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
  ArcherTower *position1tower;
  // emptyBuild *buildPos1;
  // emptyBuild *buildPos2;
  // emptyBuild *buildPos3;

  //towerPositions
  bool isTower = false;

public:
  MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
  {
    double XTowerPositions[9] = {216.4, 1023.07, 1555.07, 2021.73, 440.4, 1343.07, 1954.34, 913.73, 1693.74};
    double YTowerPositions[9] = {278.53, 379.07, 341.73, 379.07, 940.4, 796.4, 799.07, 1317.73, 1210.27};

    Background = new background();
    hg = new loadingAnimation();
    bat = new enemy();
    position1tower = new ArcherTower();
    position1tower->ArcherPosition(XTowerPositions[0], YTowerPositions[0]);
    // buildPos1 = new emptyBuild();
    // buildPos2 = new emptyBuild();
    // buildPos3 = new emptyBuild();

    // title = new Aspen::Graphics::UI::Text("M", "default", 64, this, "Title");
    // AddChild(title);
    // title->GetTransform()->SetPosition(438, 50);
    // title->GetTransform()->SetScale(0.8, 0.8);
    // title->CreateChild<Aspen::Physics::Rigidbody>();
    AddChild(Background);
    AddChild(hg);
    AddChild(bat);
    //AddChild(buildPos1);

    // buildPos1->GetTransform()->SetPosition(216.4, 278.53);
    // buildPos2->GetTransform()->SetPosition(1023.07, 379.07);
    // buildPos3->GetTransform()->SetPosition(//216.4, 278.53);
    // AddChild(sprite);
  }

  void OnUpdate()
  {
    // double xv = title->GetRigidbody()->GetVelocityX();
    // double yv = title->GetRigidbody()->GetVelocityY();

    if (Aspen::Input::KeyHeld(SDLK_1) && Aspen::Input::KeyPressed(SDLK_a) && !isTower)
    {
      AddChild(position1tower);
      isTower = true;
    }
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