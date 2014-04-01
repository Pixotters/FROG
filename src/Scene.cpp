#include "Scene.hpp"

#include "Collision/Collisionable.hpp"
#include "Collision/LSAP.hpp"

namespace frog{

  Scene::Scene()
    : State()
  {
  }

  Scene::~Scene()
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        delete(*it);
      }
    m_gameObjects.clear();
  }


  void Scene::update()
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        (*it)->update();
      }    
  }

  bool Scene::addObject(GameObject * go)
  {
    // adding the object only if it is not present
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        if(*it == go)
          {            
            return false;
          }
      }
    m_gameObjects.push_back(go);
    // adding the object's components to managers 
    sap::Collisionable * c;
    if( (c=dynamic_cast<sap::Collisionable *>(go) )  )
      {
        m_collider->addObject(c);
      }
    m_renderer->addObject(go);
    return true;
  }

  void Scene::removeObject(GameObject * go)
  {  
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        if(*it == go)
          {    
            // removing the object from managers
            m_renderer->removeObject(go);        
            // TODO : replace this crap by a component
            sap::Collisionable * c;
            if( (c=dynamic_cast<sap::Collisionable *>(go) )  ){              
              m_collider->removeObject(c);
            }
            // removing and releasing the object
            m_gameObjects.erase(it);                  
            break;
          }
      }

  }


}
