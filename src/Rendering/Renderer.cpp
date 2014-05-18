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
    auto end = m_objects.end();
    for(auto it = m_objects.begin(); it != end; it++)
      {
        updateObject( it->first );         
        draw( it->second );
      }      
    m_texture.display();
    m_target.draw( sf::Sprite(m_texture.getTexture() ) );
    m_texture.clear();
  }

  bool Renderer::addObject(const GameObject::PTR& go)
  {
    auto insert = std::pair< std::shared_ptr<GameObject>,
                             RenderingComponent *>(go, 
                                                   go->getComponent<RenderingComponent>("RENDERING").get() );    
    auto end = m_objects.end();
    auto where = m_objects.end(); // where go should be inserted
    bool found = false;
    for (auto it = m_objects.begin(); it != end; it++)
      {
        if ( it->first == go )
          {
            return false;
          }
        
        if ( not found && (it->first->transform->layer > go->transform->layer ))
          {
            /* if we found an object whose layer is higher,
               go should be inserted before. If there is no before,
               then go should be the first element of the list */
            found = true;
            where = it;
          }
      }
    
    if ( (where == m_objects.begin() ) 
         or ( where == m_objects.end() and m_objects.empty() ) )
      {
        m_objects.push_front( insert );
      }else if (where == m_objects.end() )
      {
        auto before_end = m_objects.before_begin();
        for (auto& _ : m_objects)
          ++ before_end;
        m_objects.insert_after(before_end, insert);
      }else
      {
        m_objects.insert_after(where, insert);
      }
    
    return true;
  }
  
  void Renderer::removeObject(const GameObject::PTR& go)
  {
    auto end = m_objects.end();
    for (auto it = m_objects.begin(); it != end; it++)
      {
        if (it->first == go)
          {
            m_objects.remove(*it);
            break;
          }

      }

  }

  
  void Renderer::removeObject(GameObject * go)
  {
    auto end = m_objects.end();
    for (auto it = m_objects.begin(); it != end; it++)
      {
        if (it->first.get() == go)
          {
            m_objects.remove(*it);
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
