#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Scene.hpp"

#include "Element.hpp"

#include <SFML/System/Clock.hpp>

class Level : virtual public Scene
{
  //// attributes ////
protected:
  sf::Clock m_clock;
  std::list<Element *> m_ennemies;

  //// operations ////
public:
  Level();

  virtual ~Level();
  virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
  virtual void update();

private:
   void spawn();
  void updateEnemies();
};

#endif
