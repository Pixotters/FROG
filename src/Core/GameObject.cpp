/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

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
