#include "FROG/StateManager.hpp"

#include <stack>

#include <iostream>


namespace frog{

  StateManager::StateManager()
  {
  }

  StateManager::~StateManager()
  { 
    clear();
  }

  void StateManager::push(State * s)
  {
    m_stateStack.push(s);
  }

  State * StateManager::pop()
  {
    if( m_stateStack.empty() )
      {
        std::cerr << "Cannot pop a state : StateManager is empty" << std::endl;
        return nullptr; // TODO : throw exception ??
      }
    State * s = m_stateStack.top();
    m_stateStack.pop();
    return s;
  }

  bool StateManager::isEmpty()
  {
    return m_stateStack.empty();
  }

  State * StateManager::change(State * s )
  {
    State * old = pop();
    push(s);
    return old;
  }

  void StateManager::clear()
  {
    while( !m_stateStack.empty() )
      {
        pop();
      }
  }

  void StateManager::loop(const AppInfo& appinfo)
  {
    if( not m_stateStack.empty() ) {
      State * top = m_stateStack.top();
      std::cerr << "StateManager : updating "<< top << std::endl;
      std::cerr << "StateManager :window is at "<< &appinfo.window << std::endl;
      top->update(appinfo);
      top->render(appinfo.window); 
    }
  }


}
