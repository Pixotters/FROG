#include "FROG/Scene.hpp"

#include "FROG/Collision/Collisionable.hpp"
#include "FROG/Collision/LSAP.hpp"

#include "FROG/Debug.hpp"

// TODO : try to remove that dependencies
#include <SFML/Window/Window.hpp>

#include <memory>
#include <iostream> // TODO remove

#include "FROG/XML/tinyxml2.hpp"

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

  // TODO complete
  bool Scene::loadFromFile(const std::string& file)
  {
    tinyxml2::XMLDocument doc;
    std::cerr << "Scene: loadFromFile("<< file << ")" << std::endl;
    if ( doc.LoadFile( file.c_str() ) == tinyxml2::XML_NO_ERROR )
      {
        std::cerr << "Scene: loadFromFile("<< file << ") - file loaded" << std::endl;
        tinyxml2::XMLElement * scene = doc.RootElement();
        if(scene)
          std::cerr << "scene node" << std::endl;
        tinyxml2::XMLElement * assets = scene->FirstChildElement("ASSETS");
        if(assets)
          std::cerr << "assets node" << std::endl;
        tinyxml2::XMLElement * objects = scene->FirstChildElement("OBJECTS");
        tinyxml2::XMLElement * textures = assets->FirstChildElement("TEXTURES");
        if(textures)
          std::cerr << "textures node" << std::endl;
        // loading textures 
        if(textures)         
          std::cerr << "Scene: loadFromFile("<< file << ") - textures "<< std::endl;
        for(tinyxml2::XMLElement * texture = textures->FirstChildElement();
            texture != nullptr; texture = texture->NextSiblingElement() )
          {
            std::cerr << "Scene: loadFromFile("<< file << ") - found texture" << std::endl;
            const char * file = texture->Attribute("filename");
            const char * id = texture->Attribute("ID");
            m_textureManager.loadFromFile(file, id);
          }
        //
        return true;
      } else
      {
        return false;
      }
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


