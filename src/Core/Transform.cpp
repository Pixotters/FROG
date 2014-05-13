#include "FROG/Transform.hpp"


namespace frog{

  Transform::Transform(int _layer) 
    : Component(), sf::Transformable() , layer(_layer)
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
    layer = other.layer;
  }

  Transform::~Transform()
  { 
  }

  void Transform::update(const ComponentHolder&)
  { 
    
  }

  Transform::PTR Transform::create(int l)
  {
    return PTR(new Transform(l) );
  }

}
