#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"
#include "FROG/AssetManager.hpp"

#include "Player.hpp"

#include "FontID.hpp"

#include <SFML/System/Clock.hpp>

#include <SFML/Graphics.hpp>

using namespace frog;

typedef enum {
  PLAYER_TEXTURE, 
  ENEMY_TEXTURE, 
  TARGET_TEXTURE
} TEXTURE_ID;

class Level : virtual public Scene
{
  //// attributes ////
protected:
  sf::Clock m_clock;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GameObject> m_terrain;
  std::shared_ptr<GameObject> m_gui;
  std::list< std::shared_ptr<GameObject> > m_ennemies;
  std::list< std::shared_ptr<GameObject> > m_targets;
  //  AssetManager<TEXTURE_ID, sf::Texture> m_textureManager;
  AssetManager<FONT_ID, sf::Font> m_fontManager;
  //  PhysicEngine m_phiengine;

  //// operations ////
public:
  Level();
  virtual ~Level();
  virtual void update(const AppInfo&);

private:
  void setControls(GameObject *, const AppInfo&);
  void spawnEnemy(const AppInfo&);
  void spawnTarget(const AppInfo&);
  void updateEnemies();
  void updateTargets();
};

#endif
