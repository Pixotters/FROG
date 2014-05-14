#ifndef FROG_STATEMANAGER_HPP
#define FROG_STATEMANAGER_HPP

#include "FROG/Core/FSM.hpp"

#include "FROG/Core/State.hpp"


namespace frog{

  /*!
   * StateManager helps diverting the flow by stacking states. Only the top 
   * state is updated and renderer. 
   */
  class StateManager : virtual public FSM<State>
  {

    //// operations ////
  public: 

    StateManager();

    virtual ~StateManager();

    /**
     * @brief Updates the current state
     * @param appinfo AppInfo containing the RenderTarget and delta-time
     */
    void update();


  };

}

#endif
