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
  AppInfo& m_appinfo;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GameObject> m_terrain;
  std::shared_ptr<GameObject> m_gui;
  std::list< std::shared_ptr<GameObject> > m_ennemies;
  std::list< std::shared_ptr<GameObject> > m_targets;
  AssetManager<FONT_ID, sf::Font> m_fontManager;

  //// operations ////
public:
  Level(AppInfo&);
  virtual ~Level();
  virtual void enter();
  virtual void update(const AppInfo&);

private:
  void setControls(GameObject *, const AppInfo&);
  void spawnEnemy();
  void spawnTarget();
  void updateEnemies();
  void updateTargets();
};

#endif
