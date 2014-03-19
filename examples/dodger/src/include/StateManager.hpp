#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include "Control/Controller.hpp"
#include "State.hpp"
#include <stack>

class StateManager
{

  //// attributes ////
protected:
  std::stack<State *> m_stateStack;


  //// operations ////
public: 
  StateManager();
  virtual ~StateManager();

  /**
   * @brief Push a new state at the top of the stack.
   * @details The pushed state becomes the new current state.
   * @param s State to push.
   **/
  virtual void push (State * s);

  /**
   * @brief Pops the state at the top of the stack, if there is one.
   * @details The new current state is the new top state, if exist.
   **/
  virtual State * pop();

  virtual bool isEmpty();

  /*
    @brief Changes the top state, and return the old top state.
    @details Calls pop() on the stack, pushes @a s and return the old state.
    @param s New current state replacing the top of the stack.
   */
  virtual State * change(State * s);

  /**
   * @brief Pops all the states, making the stack empty.
   */
  virtual void clear();

  /**
   * @brief Calls @e update of the current state (top of the stack).
   */
  virtual void update();
 
/**
   * @brief Draws the current state (top of the stack) in a target.
   * @param rt Target where we have draw the state. 
   */ 
  virtual void render(sf::RenderTarget& rt);


};


#endif
