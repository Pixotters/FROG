#include "FROG/Core/GameObject.hpp"

#include "FROG/XML/tinyxml2.hpp"

#include <memory>

namespace frog{

  GameObject::GameObject(GameObject * _parent)
    : ComponentHolder(), PropertiesHolder(),
      parent(_parent), transform(new Transform)
  {
    addComponent( transform, "TRANSFORM" );
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
    if (parent != nullptr)
      {
        // TODO combine with parent's transform
        /*        auto tr2 = sf::Transform::Identity;
                  tr2 *= transform->getTransform();
                  tr2 *= parent->getTransform();
                  transform->setPosition( tr2.getTransform().getPosition() );
                  transform->setRotation( tr2.getTransform().getRotation() );
                  transform->setScale( tr2.getTransform().getScale() );
        */
      }
    auto end = m_components.end();
    for(auto it = m_components.begin(); it != end; it++)
      {
        it->second->update(*this);
      }

  }

  GameObject::PTR GameObject::create(GameObject * parent)
  {
    return PTR(new GameObject(parent) );
  }

}
