#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"

#include "Player.hpp"
#include "FontID.hpp"

#include "FROG/AssetManager.hpp"
#include "FROG/AppInfo.hpp"
#include "FROG/Collision/CollisionManager.hpp"


#include <SFML/System/Clock.hpp>

#include <list>

using namespace frog;

typedef enum {
  PLAYER_TEXTURE, 
  ENEMY_TEXTURE, 
  TARGET_TEXTURE
} TEXTURE_ID;

typedef enum {
  ENEMY_TYPE,
  TARGET_TYPE
} TYPE_ID;

class Level : virtual public Scene
{
  //// attributes ////
protected:
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GameObject> m_terrain;
  std::shared_ptr<GameObject> m_gui;
  std::list< std::shared_ptr<GameObject> > m_ennemies;
  std::list< std::shared_ptr<GameObject> > m_targets;
  AssetManager<FONT_ID, sf::Font> m_fontManager;
  CollisionManager * m_collisionManager;

  //// operations ////
public:
  Level(AppInfo&);
  virtual ~Level();
  virtual void enter();
  virtual void postupdate();

private:
  void setControls(std::shared_ptr<GameObject>, const AppInfo&);
  void spawnEnemy();
  void spawnTarget();
  void updatePlayer();
  void updateEnemies();
  void updateTargets();
  void updateScore();
  void updateLives();
  void updateRow();
  void removeTarget(GameObject *);
};

#endif
