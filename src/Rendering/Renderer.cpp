#include "Rendering/Renderer.hpp"

#include "Transform.hpp"

/* TODO : no map needed, a std::set is enough, 
   and factorise (collisionManager has the same add, remove, update) */


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
      for(auto it = m_objects.begin(); it != end; it++)
        {
          updateObject( it->first );         
          draw( it->second );
        }      
      m_texture.display();
      m_target->draw( sf::Sprite(m_texture.getTexture() ) );
      m_texture.clear();
    }

    bool Renderer::addObject(GameObject * go)
    {
      return m_objects.insert(std::pair<GameObject *, RenderingComponent *>(go, nullptr) ).second;
    }

    void Renderer::removeObject(GameObject * go)
    {
      auto it = m_objects.find(go);
      if (it != m_objects.end() )
        {
          m_objects.erase(it);
        }
    }

    void Renderer::setTarget(sf::RenderTarget * rt)
    {
      m_target = rt;
    }

    void Renderer::updateObject(GameObject * go)
    {
      // TODO : see the best -> pointer comparison, dirty flag, observer ?
      RenderingComponent * rc = go->getComponent<RenderingComponent>();
      if( rc != m_objects.at(go) )
        {
          m_objects.at(go) = rc;
        }
      // TODO : check if this could be in "update" of RenderingComponent
      // or maybe we should do this in "draw"
      Transform tr = go->getTransform();
      rc->setPosition( tr.getPosition() );
      rc->setRotation( tr.getRotation() );
      rc->setScale( tr.getScale() );
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
