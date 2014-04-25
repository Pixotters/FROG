#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"
#include "FROG/Rendering/Spritesheet.hpp"
#include "FROG/AssetManager.hpp"
#include "FROG/AppInfo.hpp"
#include "FROG/GameObject.hpp"

#include <string>

class Level : virtual public frog::Scene
{

protected:
  //  frog::AssetManager<std::string, sf::Texture> m_textureManager;
  frog::AssetManager<std::string, frog::Spritesheet<std::string> > m_spritesheetManager;   // first string is ID of spritesheet, second string is ID of animations
  frog::GameObject * m_player;

public:
  Level(const frog::AppInfo&);
  virtual ~Level();
  virtual void update(const frog::AppInfo&);

};

#endif
