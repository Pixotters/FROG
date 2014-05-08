#include "FROG/StateManager.hpp"

#include "FROG/Debug.hpp"

#include <stack>

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
    s->enter();
  }

  State * StateManager::pop()
  {
    if( m_stateStack.empty() )
      {
        print_debug("Cannot pop a state : StateManager is empty");
        return nullptr; // TODO : throw exception ??
      }
    State * s = m_stateStack.top();
    m_stateStack.pop();
    s->exit();
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

  void StateManager::loop()
  {
    if( not m_stateStack.empty() ) {
      State * top = m_stateStack.top();
      top->loop();
    }
  }


}
