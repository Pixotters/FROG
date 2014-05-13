#include "FROG/Scene.hpp"

#include "FROG/XML/tinyxml2.hpp"

namespace frog{

  Scene::Scene(AppInfo& _appinfo)
    : GameState(_appinfo), renderer(appInfo.window)
  {
  }

  Scene::Scene(const Scene& other)
    : GameState(other.appInfo),
      renderer(other.appInfo.window), 
      defaultTextureManager(other.defaultTextureManager),
      defaultFontManager(other.defaultFontManager),
      defaultSoundManager(other.defaultSoundManager),
      defaultSpritesheetManager(other.defaultSpritesheetManager)
  {
  }

  Scene::Scene(const GameState& gs)
    : GameState(gs.appInfo), renderer(appInfo.window)
  {
  }

  Scene::~Scene()
  {
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
        auto scene = doc.RootElement();
        auto assets = scene->FirstChildElement("ASSETS");
        // TODO load objects ?
        //tinyxml2::XMLElement * objects = scene->FirstChildElement("OBJECTS");
        auto subassets = assets->FirstChildElement("TEXTURES");
        // TODO : try to avoid code duplication (see fillAssetManager)
        if (subassets)
          {
            for(auto asset = subassets->FirstChildElement();
                asset != nullptr; asset = asset->NextSiblingElement() )
              {
                const char * file = asset->Attribute("filename");
                const char * id = asset->Attribute("ID");                
                defaultTextureManager.loadFromFile(file, id);
              }
          }
        subassets = assets->FirstChildElement("SOUNDS");
        if (subassets)
          {
            for(auto asset = subassets->FirstChildElement();
                asset != nullptr; asset = asset->NextSiblingElement() )
              {
                const char * file = asset->Attribute("filename");
                const char * id = asset->Attribute("ID");
                defaultSoundManager.loadFromFile(file, id);
              }
          }
        subassets = assets->FirstChildElement("FONTS");
        if (subassets)
          {
            for(auto asset = subassets->FirstChildElement();
                asset != nullptr; asset = asset->NextSiblingElement() )
              {
                const char * file = asset->Attribute("filename");
                const char * id = asset->Attribute("ID");
                defaultFontManager.loadFromFile(file, id);
              }
          }
        subassets = assets->FirstChildElement("SPRITESHEETS");
        if (subassets)
          {
            for(auto asset = subassets->FirstChildElement();
                asset != nullptr; asset = asset->NextSiblingElement() )
              {
                const char * file = asset->Attribute("filename");
                const char * id = asset->Attribute("ID");
                defaultSpritesheetManager.loadFromFile(file, id);
              }
          }
        subassets = assets->FirstChildElement("TILEMAPS");
        if (subassets)
          {
            for(auto asset = subassets->FirstChildElement();
                asset != nullptr; asset = asset->NextSiblingElement() )
              {
                // TODO uncomment when Tilemaps are done
                /*            const char * file = asset->Attribute("filename");
                              const char * id = asset->Attribute("ID");
                              defaultTilemapsManager.loadFromFile(file, id);
                */
              }
          }
        return true;
      } else
      {
        return false;
      }
  }

  /* unusable because of templates
     void Scene::fillAssetManager(AssetManager& am, tinyxml2::XMLElement * e)
     {
     auto subassets = assets->FirstChildElement("TILEMAPS");
     for(auto res = e->FirstChildElement();
     res != nullptr; res = res->NextSiblingElement() )
     {
     const char * file = res->Attribute("filename");
     const char * id = res->Attribute("ID");
     am.loadFromFile(file, id);
     }
     }
  */

  void Scene::update()
  {
    preupdate();
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) 
      {
        (*it)->update();
      }
    postupdate();
    renderer.update();
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
          // TODO : possible optimization here : passing it instead of re-create
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
    renderer.addObject(go);
  }

  void Scene::removeFromEngines(const std::shared_ptr<GameObject>& go)
  {
    // removing the object from managers
    renderer.removeObject(go);     
  }

  Scene::PTR Scene::create(AppInfo& appinfo)
  {
    return PTR(new Scene(appinfo) );
  }

  Scene::PTR Scene::create(const Scene& other)
  {
    return PTR(new Scene(other) );
  }

  Scene::PTR Scene::create(const GameState& gamestate)
  {
    return PTR(new Scene(gamestate) );
  }

}





