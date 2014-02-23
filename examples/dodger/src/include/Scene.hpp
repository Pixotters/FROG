#ifndef SCENE_HPP
#define SCENE_HPP

#include "State.hpp"
#include "GameObject.hpp"

#include <list>

class Scene : virtual public State{

  //// attributes ////
protected:
  std::list<GameObject * > m_gameObjects;

  //// operations ////
public:
  Scene();

  virtual ~Scene();

  /*
    draw the scene. eg draws all the scene's gameObjects in the renderer, and draws
    the renderer in the rendertarget (in practice, in the app's window)
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  /*
    draws only the gameObjects in the renderer
   */
  virtual void drawEntities(sf::RenderTarget& rt, sf::RenderStates rs) const;

  /*
    updates the scene. eg updates all the scene's gameObjects + some codes we may 
    want to add
   */
  virtual void update();

};

#endif
