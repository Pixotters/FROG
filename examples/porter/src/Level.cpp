
#include "Level.hpp"
#include "PlayerMachine.hpp"
#include "PlayerStateFactory.hpp"
#include "MoveObject.hpp"

#include "FROG/Rendering/Animator.hpp"
#include "FROG/Rendering/Sprite.hpp"

#include "FROG/Control/ControlComponent.hpp"

#include <string>
#include <iostream>

using namespace frog;

Level::Level()
  : Scene()
{
  m_spritesheetManager.loadFromFile("assets/spritesheets/porter_animation.xml",
                                    "Porter_anim");
  m_spritesheetManager.loadFromFile("assets/spritesheets/porter_animation2.xml",
                                    "Porter_anim2");
}

Level::~Level()
{

}

bool Level::okay()
{
  return true;
}

void Level::createPlayer(const AppInfo& appinfo)
{
  m_player = new GameObject();  
  sf::Texture& tex = m_textureManager.get("PORTER_SPRITESHEET");
  Spritesheet<std::string>& sprt = m_spritesheetManager.get("Porter_anim");
  m_player->transform->layer = 2;
  m_player->addComponent< Animator<std::string> >(new Animator<std::string>(sprt, tex) );
  m_player->getComponent<Animator<std::string> >()->setDefaultAnimation("stand");
  //
  std::shared_ptr<PlayerMachine> pm(new PlayerMachine(this) );
  pm->push( PlayerStateFactory::create("stand", &okay, &okay) );
  m_player->addComponent< PlayerMachine >(pm);
  //
  std::shared_ptr<ControlComponent> ctrl(new ControlComponent(appinfo.eventList) );
  sf::Event::KeyEvent d;
  d.code = sf::Keyboard::D;
  sf::Event * e = new sf::Event();
  e->type = sf::Event::KeyPressed;
  e->key = d;
  e->key.control = 0;
  e->key.alt = 0;
  e->key.shift = 0;
  e->key.system = 0;
  ctrl->bind(e, new MoveObject(m_player, 32, 0) );
  m_player->addComponent< ControlComponent >(ctrl);
  //
  addObject(m_player);
}

void Level::createTerrain()
{
  m_terrain = new GameObject();
  m_terrain->transform->layer = 1;
  m_terrain->addComponent<Sprite>(new Sprite(m_textureManager.get("TERRAIN") ) );
  addObject(m_terrain);
}

void Level::update(const AppInfo& appinfo)
{
  static bool done = false;
  if ( not done )
    {
      createPlayer(appinfo);
      createTerrain();
      done = true;
    }
  static bool anim = false;
  if( appinfo.timer.getElapsedTime().asSeconds() > 2.0f && not anim)
    {      
      m_player->getComponent<PlayerMachine>()->change( PlayerStateFactory::create("wait", &okay, &okay) );
      anim = true;
    }
  static bool changed = false;
  if( appinfo.timer.getElapsedTime().asSeconds() > 5.0f && not changed)
    {      
      m_player->getComponent<PlayerMachine>()->change( PlayerStateFactory::create("rapping", &okay, &okay) );
      changed = true;
    }

  Scene::update(appinfo);
}