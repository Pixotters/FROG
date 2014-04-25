
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
}

Level::~Level()
{

}

void Level::update(const AppInfo& appinfo)
{
  //  std::cout << "update : timer "<<appinfo.timer.getElapsedTime().asSeconds() << std::endl;
  static bool done = false;
  if ( not done )
    {
      m_player = new GameObject();  
      sf::Texture& tex = m_textureManager.get("PORTER_SPRITESHEET");
      auto sprt = m_spritesheetManager.get("Porter_anim");
      std::cerr << "adding animator with sprt "<< &sprt << std::endl;
      std::cerr << "size is : "<< sprt.getSize() << std::endl;
      m_player->addComponent< Animator<std::string> >(new Animator<std::string>(&sprt, tex) );
      m_player->getComponent<Animator<std::string> >()->setDefaultAnimation("stand");
      done = true;
      std::cerr << "player init" << std::endl;
      addObject(m_player);
    }
  static bool anim = false;
  if( appinfo.timer.getElapsedTime().asSeconds() > 2.0f && not anim)
    {      
      m_player->getComponent<Animator<std::string> >()->playAnimation("tap_foot", true);
      anim = true;
    }
  Scene::update(appinfo);
}
