#include "FROG/Scene.hpp"

#include "FROG/Collision/Collisionable.hpp"
#include "FROG/Collision/LSAP.hpp"

#include "FROG/Debug.hpp"

// TODO : try to remove that dependencies
#include <SFML/Window/Window.hpp>

#include <iostream> // TODO remove

namespace frog{

  Scene::Scene(sf::Window& win)
    : State(), m_controller(win)
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


  void Scene::update(const AppInfo& appinfo)
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        (*it)->update();
      }    
  }

  bool Scene::addObject(GameObject * go)
  {
    // adding the object only if it is not present
    std::ostringstream err;
    err<<"Scene - addObject("<<go<<")";
    print_debug(err);
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        if(*it == go)
          {        
            err.flush();
            err.str();
            err << "Scene - addObject("<<go<<") : has already been added";
            print_debug(err);
            return false;
          }
      }
    m_gameObjects.push_back(go);
    err.flush();
    err.str();
    err << "Scene - addObject("<<go<<") : added to scene' list";
    print_debug(err);
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
