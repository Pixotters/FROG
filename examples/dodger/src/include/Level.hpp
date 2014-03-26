#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Main/Scene.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Target.hpp"

#include "Control/Controller.hpp"

#include <SFML/System/Clock.hpp>

#include <SFML/Graphics.hpp>

#include "SAPList.hpp"

using namespace frog;

class Level : virtual public Scene
{
  //// attributes ////
protected:
  sf::Clock m_clock;
  Player * m_player;
  std::list<Enemy *> m_ennemies;
  std::list<Target *> m_targets;
  //  ctrl::ControlHandler m_controller;
  SAPList * m_collider;
  //  Translator<ctrl::Input *, Command *> m_actionManager;
  ctrl::Controller m_controller;
  sf::Texture m_targetTexture;
  sf::Texture m_playerTexture;
  sf::Texture m_enemyTexture;

  //// operations ////
public:
  Level();
  virtual ~Level();
  //  virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
  virtual void update();
  void removeTarget(Target *);

private:
  void spawnEnemy();
  void spawnTarget();
  void updateEnemies();
  void updateTargets();
  void movePlayer(const short&);
};

#endif
