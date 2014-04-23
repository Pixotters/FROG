#include "FROG/GameObject.hpp"

#include "FROG/XML/tinyxml2.hpp"


#include <iostream>

namespace frog{

  GameObject::GameObject()
    : ComponentHolder()
  {

  }

  GameObject::~GameObject()
  {

  }

  bool GameObject::loadFromFile(const std::string& file)
  {
    tinyxml2::XMLDocument doc;
    if ( doc.LoadFile(file.c_str() ) ){

      return true;
    }else{
      return false;
    }
    
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
