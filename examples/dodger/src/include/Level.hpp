#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "FROG/Scene.hpp"
#include "FROG/Physics/PhysicEngine.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Target.hpp"

#include <SFML/System/Clock.hpp>

#include <SFML/Graphics.hpp>

using namespace frog;

class Level : virtual public Scene
{
  //// attributes ////
protected:
  sf::Clock m_clock;
  Player * m_player;
  std::list<Enemy *> m_ennemies;
  std::list<Target *> m_targets;
  sf::Texture m_targetTexture;
  sf::Texture m_playerTexture;
  sf::Texture m_enemyTexture;
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
