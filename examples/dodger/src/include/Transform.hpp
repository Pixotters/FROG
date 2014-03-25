#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Component.hpp"

#include <SFML/Graphics/Transformable.hpp>


class Transform : virtual public Component,
                  virtual public sf::Transformable
{
  //// attributs ////
protected:
  int m_zindex;

  //// operations ////
public:
  Transform();
  virtual ~Transform();
  virtual void update();
  int getZIndex() const;
  void setZIndex(const int& z);
};

#endif

