
#include "Level.hpp"

#include "FROG/Rendering/Animator.hpp"

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
  static bool done = false;
  if ( not done )
    {
      GameObject * g = new GameObject();  
      sf::Texture tex = m_textureManager.get("PORTER_SPRITESHEET");
      auto sprt = m_spritesheetManager.get("Porter_anim");
      std::cerr << "adding animator" << std::endl;
      g->addComponent< Animator<std::string> >(new Animator<std::string>(sprt, tex) );
      done = true;
      std::cerr << "player init" << std::endl;
    }

}
