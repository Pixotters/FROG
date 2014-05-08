#ifndef FROG_STATEMANAGER_HPP
#define FROG_STATEMANAGER_HPP

#include "FROG/State.hpp"
#include "FROG/AppInfo.hpp"
#include <stack>


namespace frog{

  /*!
   * StateManager helps diverting the flow by stacking states. Only the top 
   * state is updated and renderer. 
   */
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
     * @brief Updates and renders the current state
     * @param appinfo AppInfo containing the RenderTarget and delta-time
     */
    virtual void loop();


  };

}

#endif
