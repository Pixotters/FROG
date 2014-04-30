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

  friend class PlayerMachine;

protected:
  //  frog::AssetManager<std::string, sf::Texture> m_textureManager;
  frog::AssetManager<std::string, frog::Spritesheet<std::string> > m_spritesheetManager;   // first string is ID of spritesheet, second string is ID of animations
  frog::GameObject * m_player;
  frog::GameObject * m_terrain;  

public:
  Level();
  virtual ~Level();
  virtual void update(const frog::AppInfo&);

private:
  static bool okay();
  void createPlayer(const frog::AppInfo&);
  void createTerrain();

};

#endif
