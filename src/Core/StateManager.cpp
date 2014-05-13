#include "FROG/StateManager.hpp"

#include <stack>

namespace frog{

  StateManager::StateManager()
    : FSM<State>()
  {
  }

  StateManager::~StateManager()
  { 
    clear();
  }

  void StateManager::update()
  {
    if( not m_stack.empty() ) {
      auto top = m_stack.top();
      top->update();
    }
  }


}
