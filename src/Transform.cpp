#include "FROG/Transform.hpp"


namespace frog{

  Transform::Transform() 
    : Component(), sf::Transformable() 
  {
    setPosition(0, 0);
    setRotation(0);
    setScale(1.0f, 1.0f);
  }

  Transform::Transform(const Transform& other)
  {
    setPosition( other.getPosition() );
    setRotation( other.getRotation() );
    setScale( other.getScale() );
    setLayer( other.getLayer() );
  }

  Transform::~Transform()
  { 
  }

  void Transform::update(const ComponentHolder& parent)
  { 
    
  }

  int Transform::getLayer() const
  { 
    return m_layer; 
  }
  
  void Transform::setLayer(const int& z)
  { 
    m_layer = z; 
  }

}
