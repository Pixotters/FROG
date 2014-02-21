#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity : virtual public sf::Transformable, 
               virtual public sf::Drawable
{
  //// attributes ////
protected:
  


  //// operations ////
public : 
  Entity() : sf::Transformable(), sf::Drawable(){  }

  virtual ~Entity(){ }

  /*
    Each entity belong to a scene, and has to be drawn via the Scene's Renderer. 
    This methods has to make the first argument rendering it. 
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

  /*
    Updates the entity, simple entities may not have code here, but if we want 
    to add behaviour to an entity, it is good to put it here. 
   */
  virtual void update(const sf::Time&){ };
  
};

#endif
