#ifndef FROG_STATE_HPP
#define FROG_STATE_HPP

#include "FROG/Core/FSM.hpp"

namespace frog{

  /*!
   * A State is a point of the program. They are used by the State Manager. 
   */
  class State{

    //// operations ////
  public :

    State();

    virtual ~State();

    /*!
     * @brief function performed when StateManager enters in this state
     */
    virtual void enter();

    /*!
     * @brief Updates the state. 
     */
    virtual void update();

    /*!
     * @brief function performed when StateManager exits from the state
     */
    virtual void exit();

  };

}

#endif
