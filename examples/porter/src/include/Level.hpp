#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"
#include "FROG/Rendering/Spritesheet.hpp"
#include "FROG/AssetManager.hpp"
#include "FROG/AppInfo.hpp"
#include "FROG/GameObject.hpp"

#include <SFML/Audio/SoundBuffer.hpp>
#include <string>

class Level : virtual public frog::Scene
{

  friend class PlayerMachine;

protected:
  frog::GameObject * m_player;
  frog::GameObject * m_terrain;  

public:
  Level(frog::AppInfo&);
  virtual ~Level();
  virtual void preupdate();
  virtual void enter();

private:
  static bool okay();
  void createPlayer(const frog::AppInfo&);
  void createTerrain();

};

#endif
