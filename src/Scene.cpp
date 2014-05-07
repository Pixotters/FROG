#include "FROG/Scene.hpp"

#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/LSAP.hpp"

#include "FROG/Debug.hpp"

// TODO : try to remove that dependencies
#include <SFML/Window/Window.hpp>

#include <memory>

#include "FROG/XML/tinyxml2.hpp"

namespace frog{

  Scene::Scene()
    : State()
  {
  }

  Scene::~Scene()
  {
    m_gameObjects.clear();
  }

  // TODO complete
  bool Scene::loadFromFile(const std::string& file)
  {
    tinyxml2::XMLDocument doc;
    std::ostringstream debug;
    debug << "Scene: loading from file "<< file;
    print_debug(debug);
    debug.flush();
    if ( doc.LoadFile( file.c_str() ) == tinyxml2::XML_NO_ERROR )
      {
        tinyxml2::XMLElement * scene = doc.RootElement();
        tinyxml2::XMLElement * assets = scene->FirstChildElement("ASSETS");
        // TODO load objects ?
        //tinyxml2::XMLElement * objects = scene->FirstChildElement("OBJECTS");
        tinyxml2::XMLElement * textures = assets->FirstChildElement("TEXTURES");
        for(tinyxml2::XMLElement * texture = textures->FirstChildElement();
            texture != nullptr; texture = texture->NextSiblingElement() )
          {
            const char * file = texture->Attribute("filename");
            const char * id = texture->Attribute("ID");
            m_textureManager.loadFromFile(file, id);
          }
        return true;
      } else
      {
        return false;
      }
  }

  void Scene::enter()
  {

  }

  void Scene::update(const AppInfo&)
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) 
      {
        (*it)->update();
      }    
    m_collider -> update();
  }

  void Scene::exit()
  {

  }

  bool Scene::addObject(GameObject * go)
  {
    // adding the object only if it is not present
    std::ostringstream debug;
    debug<<"Scene - addObject("<<go<<")";
    print_debug(debug);
    auto end = m_gameObjects.end();
    for (auto it = m_gameObjects.begin(); it != end; it++)
      {
        if ( it->get() == go ) {
          debug.str("");
          debug << "Scene - addObject("<<go<<") : has already been added";
          print_debug(debug);
          debug.flush();
          return false;
        }
      }
    debug.flush();
    return addObject( std::make_shared<GameObject>(*go) );
  }

  bool Scene::addObject(const std::shared_ptr<GameObject>& go)
  {
    std::ostringstream debug;
    auto inserted = m_gameObjects.insert( std::shared_ptr<GameObject>(go) );
    if ( inserted.second ){
      std::shared_ptr<GameObject> shared(go); 
      debug << "Scene - addObject("<<go<<") : added";
      print_debug(debug);
      debug.flush();
      addToEngines( shared );
      return true;
    }
    debug << "Scene - addObject("<<go<<") : has already been added";
    print_debug(debug);
    debug.flush();
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
    m_collider->addObject( go );
    m_renderer->addObject(go);
  }

  void Scene::removeFromEngines(const std::shared_ptr<GameObject>& go)
  {
    // removing the object from managers
    m_renderer->removeObject(go);     
    m_collider->removeObject( go );
  }
}





