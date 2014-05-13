#include "FROG/GameState.hpp"

#include "FROG/Debug.hpp"

namespace frog{

  GameState::GameState(AppInfo& _appinfo)
    : State(), appInfo(_appinfo)
  {
  }

  GameState::GameState(const GameState& other)
    : State(), appInfo(other.appInfo)
  {
  }

  GameState::~GameState()
  {
    m_gameObjects.clear();
  }

  void GameState::enter()
  {
  }

  void GameState::update()
  {
    preupdate();
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) 
      {
        (*it)->update();
      }
    postupdate();
  }

  void GameState::preupdate()
  {
  }

  void GameState::postupdate()
  {
  }

  void GameState::exit()
  {
  }

  bool GameState::addObject(GameObject * go)
  {
    // adding the object only if it is not present
    std::ostringstream debug;
    debug<<"GameState - addObject("<<go<<")";
    print_debug(debug);
    auto end = m_gameObjects.end();
    for (auto it = m_gameObjects.begin(); it != end; it++)
      {
        if ( it->get() == go ) {
          debug.str("");
          debug << "GameState - addObject("<<go<<") : has already been added";
          print_debug(debug);
          debug.flush();
          return false;
        }
      }
    debug.flush();
    return m_gameObjects.insert(std::make_shared<GameObject>(*go) ).second;
  }

  bool GameState::addObject(const std::shared_ptr<GameObject>& go)
  {
    std::ostringstream debug;
    auto inserted = m_gameObjects.insert( std::shared_ptr<GameObject>(go) );
    if ( inserted.second ){
      debug << "GameState - addObject("<<go<<") : added";
      print_debug(debug);
      debug.flush();
      return true;
    }
    debug << "GameState - addObject("<<go<<") : has already been added";
    print_debug(debug);
    debug.flush();
    return false;
  }

  void GameState::removeObject(GameObject * go)
  {  
    auto end = m_gameObjects.end();
    for (auto it = m_gameObjects.begin(); it != end; it++)
      {
        if( it->get() == go ){
          m_gameObjects.erase(it);
        }
      } 
  }

  void GameState::removeObject(const std::shared_ptr<GameObject>& go)
  {  
    auto it = m_gameObjects.find(go);
    if( it != m_gameObjects.end() ) {    
      // removing and releasing the object
      m_gameObjects.erase(*it);                  
    }
  }

  GameState::PTR GameState::create(AppInfo& appinfo)
  {
    return PTR(new GameState(appinfo) );
  }

  GameState::PTR GameState::create(const GameState& other)
  {
    return PTR(new GameState(other) );
  }

}
