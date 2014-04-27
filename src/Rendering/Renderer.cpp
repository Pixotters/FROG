#include "FROG/Rendering/Renderer.hpp"

#include "FROG/Transform.hpp"

#include <iostream> // TODO remove

namespace frog{

  namespace render{

    Renderer::Renderer(sf::RenderTarget * rt,
                       const unsigned int& w,
                       const unsigned int& h)
      
    {
      // TODO : get the windows size with a service locator
      m_target = rt;
      m_texture.create(w, h);
      //      m_texture.initialize();
    }

    Renderer::Renderer(const unsigned int& w,
                       const unsigned int& h)
      
    {
      // TODO : get the windows size with a service locator
      m_texture.create(w, h);
      //      m_texture.initialize();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::update()
    {
      auto end = m_objects.end();
      std::cout << "rendering objects"<<std::endl;
      for(auto it = m_objects.begin(); it != end; it++)
        {
          std::cout << "rendering "<< it->first <<","<<it->second << std::endl;
          updateObject( it->first );         
          draw( it->second );
        }      
      m_texture.display();
      m_target->draw( sf::Sprite(m_texture.getTexture() ) );
      m_texture.clear();
    }

    bool Renderer::addObject(const std::shared_ptr<GameObject>& go)
    {
      auto insert = std::pair< std::shared_ptr<GameObject>,
                               RenderingComponent *>(go, 
                                                     go->getComponent<RenderingComponent>() );    
    auto end = m_objects.end();
    auto where = m_objects.end(); // where go should be inserted
    bool found = false;
    for (auto it = m_objects.begin(); it != end; it++)
      {
        if ( it->first == go )
          {
            return false;
          }
        
        if ( not found && ( it->first->transform->layer > go->transform->layer ))
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
        std::cout << "push front "<<go << std::endl;
        m_objects.push_front( insert );
      }else if (where == m_objects.end() )
      {
        std::cout << "insert (after end) "<<go << std::endl;
        auto before_end = m_objects.before_begin();
        for (auto& _ : m_objects)
          ++ before_end;
        m_objects.insert_after(before_end, insert);
      }else
      {
        std::cout << "insert (middle) "<<go << std::endl;
        m_objects.insert_after(where, insert);
      }
    std::cout << "added" << std::endl;
    return true;
  }
    
    void Renderer::removeObject(const std::shared_ptr<GameObject>& go)
    {
      // TODO
      //      m_objects.remove(go);
    }

  void Renderer::setTarget(sf::RenderTarget * rt)
  {
    m_target = rt;
  }

  void Renderer::updateObject(const std::shared_ptr<GameObject>& go)
  {
    /* TODO : check if RenderingComponent or layer changed. 
       see the best -> pointer comparison, dirty flag, observer, notifying ?
    */
    /*    RenderingComponent * rc = go->getComponent<RenderingComponent>();
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


}

  }
