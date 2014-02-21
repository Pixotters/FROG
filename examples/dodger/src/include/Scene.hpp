#ifndef SCENE_HPP
#define SCENE_HPP

#include "State.hpp"
#include "Entity.hpp"

#include <list>

class Scene : virtual public State{

  //// attributes ////
protected:
  std::list<Entity * > m_entities;

  //// operations ////
public:
  Scene();
  virtual ~Scene();
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
  virtual void update(const sf::Time&);

};

#endif
