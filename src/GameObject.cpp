#include "FROG/GameObject.hpp"

#include "FROG/XML/tinyxml2.hpp"

#include "FROG/Rendering/Sprite.hpp" // TODO remove

#include <iostream>
#include <memory>

namespace frog{

  GameObject::GameObject()
    : ComponentHolder()
  {
    addComponent(std::shared_ptr<Transform>(&transform) );
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
    std::cerr << "GameObject: update() : "<< m_components.size() << std::endl;
    auto end = m_components.end();
    for(auto it = m_components.begin(); it != end; it++)
      {
        std::cerr << "GameObject: update() - updating "<< *it << std::endl;
        std::shared_ptr<Sprite> s;
        if( (s = std::dynamic_pointer_cast<Sprite>(*it) ) ){
          std::cerr << "GameObject: update(), it's a Sprite !" << std::endl;
        }
        (*it)->update(*this);
        std::cerr << "GameObject: update() - updated "<< (*it).get() << std::endl;

      }

  }
 

}
