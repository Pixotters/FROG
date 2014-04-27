
#include "Level.hpp"

#include "FROG/Rendering/Animator.hpp"
#include "FROG/Rendering/Sprite.hpp"

#include <string>
#include <iostream>

using namespace frog;

Level::Level(const AppInfo& appinfo)
  : Scene(appinfo.window)
{
  m_spritesheetManager.loadFromFile("assets/spritesheets/porter_animation.xml",
                                    "Porter_anim");
  m_spritesheetManager.loadFromFile("assets/spritesheets/porter_animation2.xml",
                                    "Porter_anim2");
}

Level::~Level()
{

}

void Level::update(const AppInfo& appinfo)
{
  static bool done = false;
  if ( not done )
    {
      m_player = new GameObject();  
      sf::Texture& tex = m_textureManager.get("PORTER_SPRITESHEET");
      Spritesheet<std::string>& sprt = m_spritesheetManager.get("Porter_anim");
      m_player->addComponent< Animator<std::string> >(new Animator<std::string>(sprt, tex) );
      m_player->getComponent<Animator<std::string> >()->setDefaultAnimation("stand");
      m_terrain = new GameObject();
      //      m_terrain->addComponent<Sprite>(new Sprite(m_textureManager.get("TERRAIN") ) );
      addObject(m_terrain);
      addObject(m_player);
      done = true;
    }
  static bool anim = false;
  if( appinfo.timer.getElapsedTime().asSeconds() > 2.0f && not anim)
    {      
      m_player->getComponent<Animator<std::string> >()->playAnimation("tap_foot", true);
      anim = true;
    }
  static bool changed = false;
  if( appinfo.timer.getElapsedTime().asSeconds() > 5.0f && not changed)
    {      
      m_player->getComponent<Animator<std::string> >()->changeTexture(m_textureManager.get("PORTER2_SPRITESHEET") );
      m_player->getComponent<Animator<std::string> >()->changeSpritesheet(m_spritesheetManager.get("Porter_anim2") );
      changed = true;
    }

  Scene::update(appinfo);
}
