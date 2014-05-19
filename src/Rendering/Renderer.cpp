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
