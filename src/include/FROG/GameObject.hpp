#ifndef FROG_GAMEOBJECT_HPP
#define FROG_GAMEOBJECT_HPP

#include "FROG/Transform.hpp"
#include "FROG/ComponentHolder.hpp"

#include <SFML/Graphics.hpp>


namespace frog{

  class GameObject : virtual public sf::Drawable,
                     virtual public ComponentHolder
  {
    //// attributes ////
  protected:
    Transform m_transform;

    //// operations ////
  public : 
    GameObject();

    virtual ~GameObject();

    /*
      Each gameObject belong to a scene, and has to be drawn via the Scene's Renderer. 
      This methods has to make the first argument rendering it. 
    */
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    /*
      Updates the gameObject, simple gameObjects may not have code here, but if we want 
      to add behaviour to an gameObject, it is good to put it here. 
    */
    virtual void update();
  
    Transform getTransform() const;
    Transform& getTransform();
    //    virtual Transform * getComponent<Transform>();
  };

}

#endif
