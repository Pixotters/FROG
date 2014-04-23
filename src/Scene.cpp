#include "FROG/Scene.hpp"

#include "FROG/Collision/Collisionable.hpp"
#include "FROG/Collision/LSAP.hpp"

#include "FROG/Debug.hpp"

// TODO : try to remove that dependencies
#include <SFML/Window/Window.hpp>

#include <memory>
#include <iostream> // TODO remove

namespace frog{

  Scene::Scene(sf::Window& win)
    : State(), m_controller(win)
  {
  }

  Scene::~Scene()
  {
    //    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
    //      delete(*it);
    //    }
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
    //    print_debug("Scene - addObject(raw"+go+")");
    auto end = m_gameObjects.end();
    for (auto it = m_gameObjects.begin(); it != end; it++)
      {
        if ( it->get() == go ) {
          break;
        }
      }
    return addObject( std::make_shared<GameObject>(*go) );
  }

  bool Scene::addObject(const std::shared_ptr<GameObject>& go)
  {
    //    print_debug("Scene - addObject(shared"+go.get()+") : added to scene' list");
    auto inserted = m_gameObjects.insert( std::shared_ptr<GameObject>(go) );
    if ( inserted.second ){
      std::shared_ptr<GameObject> shared(go); 
      addToEngines( shared );
      return true;
    }
    //    print_debug("Scene - addObject(shared"+go.get()+") : has already been added");
    return false;
  }

  void Scene::removeObject(GameObject * go)
  {  
    auto end = m_gameObjects.end();
    for (auto it = m_gameObjects.begin(); it != end; it++)
      {
        if( it->get() == go ){
          std::shared_ptr<GameObject> shared(*it);
          removeFromEngines(shared);
          m_gameObjects.erase(it);
        }
      } 
  }

  void Scene::removeObject(const std::shared_ptr<GameObject>& go)
  {  
    auto it = m_gameObjects.find(go);
    if( it != m_gameObjects.end() ) {    
      // removing and releasing the object
      removeFromEngines(*it);
      m_gameObjects.erase(*it);                  
    }
  }

  void Scene::addToEngines(const std::shared_ptr<GameObject>& go)
  {
    sap::Collisionable * c;
    if( (c = dynamic_cast<sap::Collisionable *>( go.get() ) )  ) {
      m_collider->addObject(c);
    }
    m_renderer->addObject(go);
  }

  void Scene::removeFromEngines(const std::shared_ptr<GameObject>& go)
  {
    // removing the object from managers
    m_renderer->removeObject(go);        
    // TODO : replace this crap by a component
    sap::Collisionable * c;
    if( (c = dynamic_cast<sap::Collisionable *>( go.get() ) )  ){ 
      m_collider->removeObject(c);
    }
  }

}


