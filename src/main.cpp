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
#include "Enemy.hpp"
#include "emptyBuild.cpp"
#include "Tower.cpp"
#include <iostream>

using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;

int playerHealth = 10;

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

// class loadingAnimation : public Aspen::Graphics::Animation
// {
// public:
//   loadingAnimation(Object *parent = nullptr, std::string name = "loadingAnimation") : Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/hourglass.png", 480, 480, 113, nullptr, "HourglassSpritesheet"), 1.0f / 20.0f, this, "Hourglass")
//   {
//     GetTransform()->SetPosition(640, 360);
//   }
// };

class MainMenu : public GameState
{
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::Animation *sprite;
  Aspen::Graphics::Animation *playerhealthbar;
  //loadingAnimation *hg;
  background *Background;

  // int batSpawnCD = 0;
  // int batSpawnTime = 300;
  // int batNum = 1;

  //towerPositions
  bool isTower[9] = {false, false, false, false, false, false, false, false, false};

public:
  MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)
  {
    Background = new background();
    //hg = new loadingAnimation();
    bat = new enemy();
    playerhealthbar = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/healthbar.png", 256, 256, 11, nullptr, "HealthBar"), 0, this, "Animation");
    // buildPos1 = new emptyBuild();
    // buildPos2 = new emptyBuild();
    // buildPos3 = new emptyBuild();

    // title = new Aspen::Graphics::UI::Text("M", "default", 64, this, "Title");
    // AddChild(title);
    // title->GetTransform()->SetPosition(438, 50);
    // title->GetTransform()->SetScale(0.8, 0.8);
    // title->CreateChild<Aspen::Physics::Rigidbody>();
    AddChild(Background);
    //AddChild(hg);
    AddChild(new enemy());

    AddChild(bat);
    AddChild(playerhealthbar);
    playerhealthbar->GetTransform()->SetPosition(50.5, 20.5);
    playerhealthbar->GetTransform()->SetScale(2, 2);
    //AddChild(buildPos1);

    // buildPos1->GetTransform()->SetPosition(216.4, 278.53);
    // buildPos2->GetTransform()->SetPosition(1023.07, 379.07);
    // buildPos3->GetTransform()->SetPosition(//216.4, 278.53);
    // AddChild(sprite);
  }

  void OnUpdate()
  {
    // batSpawnCD++;
    // if (batSpawnCD >= batSpawnTime)
    // {
    //   AddChild(new enemy());
    //   batNum++;
    //   batSpawnCD = 0;
    // }

    float hpbar1 = (1 - float(playerHealth) / float(10)) * playerhealthbar->GetFrameCount();
    playerhealthbar->SetFrame(playerHealth <= 0 ? 10 : int(hpbar1));

    if (playerHealth <= 0)
    {
      Aspen::Log::Debug("Game lost!");
    }

    // double xv = title->GetRigidbody()->GetVelocityX();
    // double yv = title->GetRigidbody()->GetVelocityY();
    double XTowerPositions[9] = {
        309.4,
        1505.07,
        2288.07,
        2970.73,
        642.4,
        1979.7,
        2875.34,
        1345.73,
        2488.74};
    double YTowerPositions[9] = {
        288.53,
        438.07,
        384.73,
        438.07,
        1263.4,
        1053.4,
        1056.7,
        1818.73,
        1665.27};
    //tower position 1
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_1) && !isTower[0])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[0], YTowerPositions[0]);
      AddChild(posTower);
      isTower[0] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_1) && !isTower[0])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[0], YTowerPositions[0]);
      AddChild(posTower);
      isTower[0] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_1) && !isTower[0])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[0], YTowerPositions[0]);
      AddChild(posTower);
      isTower[0] = true;
    }
    //tower position 2
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_2) && !isTower[1])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[1], YTowerPositions[1]);
      AddChild(posTower);
      isTower[1] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_2) && !isTower[1])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[1], YTowerPositions[1]);
      AddChild(posTower);
      isTower[1] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_2) && !isTower[1])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[1], YTowerPositions[1]);
      AddChild(posTower);
      isTower[1] = true;
    }
    //tower position 3
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_3) && !isTower[2])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[2], YTowerPositions[2]);
      AddChild(posTower);
      isTower[2] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_3) && !isTower[2])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[2], YTowerPositions[2]);
      AddChild(posTower);
      isTower[2] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_3) && !isTower[2])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[2], YTowerPositions[2]);
      AddChild(posTower);
      isTower[2] = true;
    }
    //tower position 4
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_4) && !isTower[3])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[3], YTowerPositions[3]);
      AddChild(posTower);
      isTower[3] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_4) && !isTower[3])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[3], YTowerPositions[3]);
      AddChild(posTower);
      isTower[3] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_4) && !isTower[3])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[3], YTowerPositions[3]);
      AddChild(posTower);
      isTower[3] = true;
    }
    //tower position 5
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_5) && !isTower[4])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[4], YTowerPositions[4]);
      AddChild(posTower);
      isTower[4] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_5) && !isTower[4])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[4], YTowerPositions[4]);
      AddChild(posTower);
      isTower[4] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_5) && !isTower[4])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[4], YTowerPositions[4]);
      AddChild(posTower);
      isTower[4] = true;
    }
    //tower position 6
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_6) && !isTower[5])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[5], YTowerPositions[5]);
      AddChild(posTower);
      isTower[5] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_6) && !isTower[5])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[5], YTowerPositions[5]);
      AddChild(posTower);
      isTower[5] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_6) && !isTower[5])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[5], YTowerPositions[5]);
      AddChild(posTower);
      isTower[5] = true;
    }
    //tower position 7
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_7) && !isTower[6])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[6], YTowerPositions[6]);
      AddChild(posTower);
      isTower[6] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_7) && !isTower[6])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[6], YTowerPositions[6]);
      AddChild(posTower);
      isTower[6] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_7) && !isTower[6])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[6], YTowerPositions[6]);
      AddChild(posTower);
      isTower[6] = true;
    }
    //tower position 8
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_8) && !isTower[7])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[7], YTowerPositions[7]);
      AddChild(posTower);
      isTower[7] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_8) && !isTower[7])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[7], YTowerPositions[7]);
      AddChild(posTower);
      isTower[7] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_8) && !isTower[7])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[7], YTowerPositions[7]);
      AddChild(posTower);
      isTower[7] = true;
    }
    //tower position 9
    if (Aspen::Input::KeyHeld(SDLK_a) && Aspen::Input::KeyPressed(SDLK_9) && !isTower[8])
    {
      ArcherTower *posTower;
      posTower = new ArcherTower();
      posTower->ArcherPosition(XTowerPositions[8], YTowerPositions[8]);
      AddChild(posTower);
      isTower[8] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_m) && Aspen::Input::KeyPressed(SDLK_9) && !isTower[8])
    {
      MageTower *posTower;
      posTower = new MageTower();
      posTower->MagePosition(XTowerPositions[8], YTowerPositions[8]);
      AddChild(posTower);
      isTower[8] = true;
    }
    else if (Aspen::Input::KeyHeld(SDLK_b) && Aspen::Input::KeyPressed(SDLK_9) && !isTower[8])
    {
      BoulderTower *posTower;
      posTower = new BoulderTower();
      posTower->BoulderPosition(XTowerPositions[8], YTowerPositions[8]);
      AddChild(posTower);
      isTower[8] = true;
    }

    // if (Aspen::Input::KeyHeld(SDLK_1) && !isTower1)
    // {
    //   defTower(SDLK_1, SDLK_a, 0);
    // }
    // else if (Aspen::Input::KeyHeld(SDLK_2) && Aspen::Input::KeyPressed(SDLK_a) && !isTower2)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[1], YTowerPositions[1]);
    //   AddChild(posTower);
    //   isTower2 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_3) && Aspen::Input::KeyPressed(SDLK_a) && !isTower3)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[2], YTowerPositions[2]);
    //   AddChild(posTower);
    //   isTower3 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_4) && Aspen::Input::KeyPressed(SDLK_a) && !isTower4)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[3], YTowerPositions[3]);
    //   AddChild(posTower);
    //   isTower4 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_5) && Aspen::Input::KeyPressed(SDLK_a) && !isTower5)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[4], YTowerPositions[4]);
    //   AddChild(posTower);
    //   isTower5 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_6) && Aspen::Input::KeyPressed(SDLK_a) && !isTower6)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[5], YTowerPositions[5]);
    //   AddChild(posTower);
    //   isTower6 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_7) && Aspen::Input::KeyPressed(SDLK_a) && !isTower7)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[6], YTowerPositions[6]);
    //   AddChild(posTower);
    //   isTower7 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_8) && Aspen::Input::KeyPressed(SDLK_a) && !isTower8)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[7], YTowerPositions[7]);
    //   AddChild(posTower);
    //   isTower8 = true;
    // }

    // else if (Aspen::Input::KeyHeld(SDLK_9) && Aspen::Input::KeyPressed(SDLK_a) && !isTower9)
    // {
    //   ArcherTower *posTower;
    //   posTower = new ArcherTower();
    //   posTower->ArcherPosition(XTowerPositions[8], YTowerPositions[8]);
    //   AddChild(posTower);
    //   isTower9 = true;
    // }
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
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
  //engine.FindChildOfType<GameStateManager>()->LoadState<Game>(false);

  while (engine)
    engine();
  return 0;
};