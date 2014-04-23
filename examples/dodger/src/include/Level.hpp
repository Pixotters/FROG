#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"
#include "FROG/Physics/PhysicEngine.hpp"
#include "FROG/AssetManager.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Target.hpp"

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
  std::list< std::shared_ptr<Enemy> > m_ennemies;
  std::list< std::shared_ptr<Target> > m_targets;
  AssetManager<TEXTURE_ID, sf::Texture> m_textureManager;
  //  PhysicEngine m_phiengine;

  //// operations ////
public:
  Level(const AppInfo& );
  virtual ~Level();
  virtual void update(const AppInfo&);
  void removeTarget(Target *);

private:
  void spawnEnemy();
  void spawnTarget();
  void updateEnemies();
  void updateTargets();
  void movePlayer(const short&);
};

#endif
