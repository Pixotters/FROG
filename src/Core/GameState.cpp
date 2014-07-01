/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#include "FROG/Core/GameState.hpp"

#include "FROG/Core/Debug.hpp"

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

  bool GameState::addObject(const GameObject::PTR& go)
  {
    std::ostringstream debug;
    auto inserted = m_gameObjects.insert( GameObject::PTR(go) );
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

  void GameState::removeObject(const GameObject::PTR& go)
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
