#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject : virtual public sf::Transformable, 
               virtual public sf::Drawable
{
  //// attributes ////
protected:
  


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
  
};

#endif
