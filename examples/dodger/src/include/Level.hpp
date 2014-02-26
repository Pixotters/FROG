#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Scene.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include <SFML/System/Clock.hpp>

class Level : virtual public Scene
{
  //// attributes ////
protected:
  sf::Clock m_clock;
  std::list<Enemy *> m_ennemies;
  std::list<Target *> m_targets;

  //// operations ////
public:
  Level();
  virtual ~Level();
  virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
  virtual void update();

private:
  void spawnEnemy();
  void spawnTarget();
  void updateEnemies();
  void updateTargets();
};

#endif
