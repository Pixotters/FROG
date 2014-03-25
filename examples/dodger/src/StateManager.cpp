#include "StateManager.hpp"

#include <stack>

#include <iostream>


namespace frog{

  StateManager::StateManager()
  {
  }

  StateManager::~StateManager()
  { 
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

  void StateManager::update()
  {
    if( not m_stateStack.empty() )
      {
        m_stateStack.top()->update();
      }
  }

  void StateManager::render(sf::RenderTarget& rt)
  {
    if( not m_stateStack.empty() )
      {
        m_stateStack.top()->draw(rt, sf::RenderStates::Default);
      }
  }

}
