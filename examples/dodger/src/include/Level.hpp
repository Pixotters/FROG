#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Rendering/Scene.hpp"

#include "Player.hpp"

#include "FROG/Core/AssetManager.hpp"
#include "FROG/Core/AppInfo.hpp"
#include "FROG/Collision/CollisionManager.hpp"


#include <SFML/Audio/Music.hpp>
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
  //  sf::Music m_music;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GameObject> m_terrain;
  std::shared_ptr<GameObject> m_gui;
  std::list< std::shared_ptr<GameObject> > m_enemies;
  std::list< std::shared_ptr<GameObject> > m_targets;
  CollisionManager * m_collisionManager;

  //// operations ////
public:
  Level(AppInfo&);
  Level(const Scene&);
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
  void removeTarget(std::shared_ptr<GameObject>);
};

#endif
