#include "FROG/GameObject.hpp"

#include "FROG/XML/tinyxml2.hpp"

#include "FROG/Rendering/Sprite.hpp" // TODO remove

#include <iostream>
#include <memory>

namespace frog{

  GameObject::GameObject()
    : ComponentHolder()
  {
    addComponent(std::shared_ptr<Transform>( &transform ) );
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
    auto end = m_components.end();
    for(auto it = m_components.begin(); it != end; it++)
      {
        (*it)->update(*this);
      }

  }
 

}
