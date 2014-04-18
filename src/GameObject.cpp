#include "FROG/GameObject.hpp"

#include <iostream>

namespace frog{

  GameObject::GameObject()
    : sf::Drawable() 
  {

  }

  GameObject::~GameObject()
  {
#ifdef DEBUG
    std::cerr << "Destroying GameObject "<< this << std::endl;
#endif
  }


  void GameObject::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
  {
    rs.transform *= m_transform.getTransform();
  }


  void GameObject::update()
  { 

  }

  Transform GameObject::getTransform() const
  {
    return m_transform;
  }

  Transform& GameObject::getTransform()
  {
    return m_transform;
  }

   Transform * GameObject::getPTransform()
  {
    return &m_transform;
  }
 
}
