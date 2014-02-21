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
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
  virtual void update(const sf::Time&){ };
  
};

#endif
