#ifndef SCENE_HPP
#define SCENE_HPP

#include "State.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"

#include <list>

class Scene : virtual public State{

  //// attributes ////
protected:
  std::list<Entity * > m_entities;
  Renderer * m_renderer;

  //// operations ////
public:
  Scene();

  virtual ~Scene();

  /*
    draw the scene. eg draws all the scene's entities in the renderer, and draws
    the renderer in the rendertarget (but n fact, it is always the app's 
    window...
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  /*
    updates the scene. eg updates all the scene's entities + some codes we may 
    want to add
   */
  virtual void update(const sf::Time&);

};

#endif
