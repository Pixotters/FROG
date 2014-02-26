#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Component.hpp"

#include <SFML/Graphics/Transformable.hpp>


class Transform : virtual public Component,
                  virtual public sf::Transformable
{
  //// operations ////
public:
  Transform() : Component(), sf::Transformable() {} ;
  virtual ~Transform(){ };
  virtual void update(){ };
};

#endif

