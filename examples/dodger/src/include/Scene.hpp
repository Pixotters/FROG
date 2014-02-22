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

  /*
    draw the scene. eg draws all the scene's entities in the renderer, and draws
    the renderer in the rendertarget (in practice, in the app's window)
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  /*
    draws only the entities in the renderer
   */
  virtual void drawEntities(sf::RenderTarget& rt, sf::RenderStates rs) const;

  /*
    updates the scene. eg updates all the scene's entities + some codes we may 
    want to add
   */
  virtual void update(const sf::Time&);

};

#endif
