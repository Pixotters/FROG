
#include "Level.hpp"
#include "PlayerMachine.hpp"
#include "PlayerStateFactory.hpp"
#include "MoveObject.hpp"

#include "FROG/Rendering/Animator.hpp"
#include "FROG/Rendering/Sprite.hpp"

#include "FROG/Component/AudioSource.hpp"

#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/MouseButton.hpp"
#include "FROG/Control/JoystickButton.hpp"
#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Control/Xbox.hpp"

#include <string>
#include <iostream>

using namespace frog;

Level::Level()
  : Scene()
{
  defaultSpritesheetManager.loadFromFile("assets/spritesheets/porter_animation.xml",
                                    "Porter_anim");
  defaultSpritesheetManager.loadFromFile("assets/spritesheets/porter_animation2.xml",
                                    "Porter_anim2");
  defaultSoundManager.loadFromFile("assets/sounds/metal_gong.wav",
                                    "METAL_GONG");
  defaultSoundManager.loadFromFile("assets/sounds/woosh.wav",
                                    "WOOSH");
}

Level::~Level()
{

}

bool Level::okay()
{
  return true;
}

void Level::createPlayer(const AppInfo& appInfo)
{
  m_player = new GameObject();  
  sf::Texture& tex = defaultTextureManager.get("PORTER_SPRITESHEET");
  Spritesheet<std::string>& sprt = defaultSpritesheetManager.get("Porter_anim");
  m_player->transform->layer = 2;
  m_player->addComponent(new Animator<std::string>(sprt, tex), 
                         "RENDERING" );
  m_player->addComponent(new AudioSource, 
                         "AUDIO" );
  m_player->getComponent<Animator<std::string> >("RENDERING")->setDefaultAnimation("stand");
  //
  std::shared_ptr<PlayerMachine> pm(new PlayerMachine(this) );
  pm->push( PlayerStateFactory::create("stand", &okay, &okay) );
  m_player->addComponent(pm, "FSM");
  //
  std::shared_ptr<ControlComponent> ctrl(new ControlComponent(appInfo.eventList) );
  auto u = KeyboardButton::create(sf::Keyboard::Z);
  auto d = KeyboardButton::create(sf::Keyboard::S);
  auto l = KeyboardButton::create(sf::Keyboard::Q, Trigger::RELEASED);
  auto r = KeyboardButton::create(sf::Keyboard::D, Trigger::PRESSED);
  auto lm = MouseButton::create(sf::Mouse::Left, Trigger::PRESSED);
  auto rm = MouseButton::create(sf::Mouse::Right, Trigger::PRESSED);
  ctrl->bind(u, new MoveObject(m_player, 0, -32) );
  ctrl->bind(d, new MoveObject(m_player, 0, 32) );
  ctrl->bind(l, new MoveObject(m_player, -32, 0) );
  ctrl->bind(lm, new MoveObject(m_player, -32, 0) );
  ctrl->bind(r, new MoveObject(m_player, 32, 0) );
  ctrl->bind(rm, new MoveObject(m_player, 32, 0) );
  JoystickButton * j = new JoystickButton(XBOX::A, Trigger::PRESSED);
  ctrl->bind(j, new MoveObject(m_player, 0, 32) );
  m_player->addComponent(ctrl, "CONTROL");
  //
  addObject(m_player);
}

void Level::createTerrain()
{
  m_terrain = new GameObject();
  m_terrain->transform->layer = 1;
  m_terrain->addComponent(std::shared_ptr<Sprite>(new Sprite(defaultTextureManager.get("TERRAIN") ) ), 
                          "RENDERING" );
  addObject(m_terrain);
}

void Level::enter()
{
  createPlayer(appInfo);
  createTerrain();
}

void Level::preupdate()
{
  static bool anim = false;
  if( appInfo.timer.getElapsedTime().asSeconds() > 2.0f && not anim)
    {      
      m_player->getComponent<PlayerMachine>("FSM")->change( PlayerStateFactory::create("wait", &okay, &okay) );
      anim = true;
    }
  static bool changed = false;
  if( appInfo.timer.getElapsedTime().asSeconds() > 5.0f && not changed)
    {      
      m_player->getComponent<PlayerMachine>("FSM")->change( PlayerStateFactory::create("rapping", &okay, &okay) );
      changed = true;
    }
}
