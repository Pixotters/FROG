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
    print_debug("StateManager - loop("+&appinfo+")");
    if( not m_stateStack.empty() ) {
      print_debug("StateManager - loop("+&appinfo+") : not empty");
      State * top = m_stateStack.top();
      print_debug("StateManager - loop("+&appinfo+") : updating "+top);
      top->update(appinfo);
      print_debug("StateManager - loop("+&appinfo+") : rendering "+top);
      top->render(appinfo.window); 
    }
  }


}
