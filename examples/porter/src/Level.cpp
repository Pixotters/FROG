#include "Level.hpp"

#include "FROG/Rendering/Animator.hpp"

#include <string>

using namespace frog;

Level::Level(const AppInfo& appinfo)
  : Scene(appinfo.window)
{
  m_spritesheetManager.loadFromFile("assets/spritesheets/porter_animation.xml");
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
      Spritesheet sprt = m_spritesheetManager.get("");
      g->addComponent< Animator<std::string> >(new Animator(sprt, tex) );
      done = true;
    }

}
