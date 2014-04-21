#include "FROG/GameObject.hpp"

#include <iostream>

namespace frog{

  GameObject::GameObject()
    : ComponentHolder()
  {

  }

  GameObject::~GameObject()
  {
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
