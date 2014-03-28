#include "Transform.hpp"


namespace frog{

  Transform::Transform() 
    : Component(), sf::Transformable() 
  {
  }

  Transform::~Transform()
  { 
  }

  void Transform::update()
  { 
  }

  int Transform::getZIndex() const
  { 
    return m_zindex; 
  }
  
  void Transform::setZIndex(const int& z)
  { 
    m_zindex = z; 
  }

}