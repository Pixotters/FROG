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
    std::cerr << "adding object "<<go<<std::endl;
    // adding the object only if it is not present
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        if(*it == go)
          {            
            std::cerr << "already added  "<<go<<std::endl;
            return false;
          }
      }
    m_gameObjects.push_back(go);
    // adding the object's components to managers 
    sap::Collisionable * c;
    if( (c=dynamic_cast<sap::Collisionable *>(go) )  )
      {
        std::cerr << "adding "<<go<<" to collider "<<m_collider<<std::endl;
        m_collider->addObject(c);
      }
    std::cerr << "adding "<<go<<" to renderer "<<m_renderer<<std::endl;
    m_renderer->addObject(go);
    std::cerr << "added  "<<go<<std::endl;
    return true;
  }

  void Scene::removeObject(GameObject * go)
  {  
    std::cerr << "removing object "<<go<<std::endl;
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        if(*it == go)
          {    
            std::cerr << "was here "<<go<<std::endl;
            // removing the object from managers
            std::cerr << "removing "<<go<<" from renderer "<<m_renderer<<std::endl;
            m_renderer->removeObject(go);        
            // TODO : replace this crap by a component
            sap::Collisionable * c;
            if( (c=dynamic_cast<sap::Collisionable *>(go) )  ){              
              std::cerr << "removing "<<go<<" from collider "<<m_collider<<std::endl;
              m_collider->removeObject(c);
            }
            // removing and releasing the object
            m_gameObjects.erase(it);                  
            break;
          }
      }

  }


}
