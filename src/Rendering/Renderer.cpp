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

#include "FROG/Rendering/Renderer.hpp"
#include "FROG/Core/Transform.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace frog{

  Renderer::Renderer(sf::RenderTarget& rt)
    : m_target(rt)
  {
    m_texture.create(m_target.getSize().x, m_target.getSize().y);
    camera.reset(sf::FloatRect(0, 0,
                               m_target.getSize().x, 
                               m_target.getSize().y) );
    updateCamera();
  }
  
  Renderer::Renderer(sf::RenderTarget& rt,
                     unsigned int w,
                     unsigned int h)
    : m_target(rt)  
  {
    m_texture.create(w, h);
    camera.reset(sf::FloatRect(0, 0, w, h) );
    updateCamera();
  }

  Renderer::~Renderer()
  {
    m_objects.clear();
  }

  void Renderer::update()
  {
    for(auto& it : m_objects)
      {
        updateObject( it.first );         
        draw( it.second );
      }      
    m_texture.display();
    m_target.draw( sf::Sprite(m_texture.getTexture() ) );
    m_texture.clear();
  }
  
  struct comparator
  {
    inline bool operator() (const std::pair<GameObject::PTR, RenderingComponent *>& a,
                            const std::pair<GameObject::PTR, RenderingComponent *>& b)
    { 
      return (a.first->transform->layer) < (b.first->transform->layer);
    }
  };

  bool Renderer::addObject(const GameObject::PTR& go)
  {
    try
      {
        auto insert = std::pair< GameObject::PTR, RenderingComponent *> \
          (go, go->getComponent<RenderingComponent>("RENDERING").get() ); 
        // checking that element is not already present
        auto end = m_objects.end();
        for (auto it = m_objects.begin(); it != end; it++)
          {
            if ( it->first == go )
              {
                return false;
              }     
          }
        m_objects.push_back(insert);
        // sort by layer : lower layer displayed first
        std::sort (m_objects.begin(), m_objects.end(), comparator() );
        return true;
      }catch(std::logic_error e)
      {
        return false;
      }
  
  }
  
  void Renderer::removeObject(const GameObject::PTR& go)
  {
    auto end = m_objects.end();
    for (auto it = m_objects.begin(); it != end; it++)
      {
        if (it->first == go)
          {
            m_objects.erase(it);
            // objects are, by construction, unique in the vector
            break;
          }
      }
  }

  
  void Renderer::updateObject(const GameObject::PTR& go)
  {
    /* TODO : check if RenderingComponent or layer changed. 
       see the best -> pointer comparison, dirty flag, observer, notifying ?
    */
    /*    RenderingComponent * rc = go->getComponent<RenderingComponent>("RENDERING");
          if( rc != m_objects.at(go) )
          {
          m_objects.at(go) = rc;
          }
    */
  }
  
  void Renderer::draw(RenderingComponent * rc)
  {
    if(rc != nullptr)
      {
        rc->draw(m_texture, rc->getTransform() );
      }
  }

  void Renderer::updateCamera()
  {
    m_texture.setView(camera);
    
  }

  void Renderer::resizeCamera(const sf::FloatRect& zone)
  {
    camera.reset(zone);
    updateCamera();
  }

  Renderer::PTR Renderer::create(sf::RenderTarget& rt,
                                 unsigned int w, 
                                 unsigned int h)
  {
    return PTR(new Renderer(rt, w, h) );
  }

  Renderer::PTR Renderer::create(sf::RenderTarget& rt)
  {
    return PTR(new Renderer(rt) );
  }
  
}
