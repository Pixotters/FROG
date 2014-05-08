#ifndef FROG_STATE_HPP
#define FROG_STATE_HPP

namespace frog{

  /*!
   * A State is a point of the program. They are used by the State Manager. 
   */
  class State{

    friend class StateManager;

    //// operations ////
  public :

    State();

    virtual ~State();

    /*!
     * @brief Updates the state
     */
    void loop();

  protected:

    /*!
     * @brief function performed when StateManager enters in this state
     */
    virtual void enter() = 0;

    /*!
     * @brief Updates the state. 
     */
    virtual void update() = 0;

    /*!
     * @brief function performed when StateManager exits from the state
     */
    virtual void exit() = 0;

  };

}

#endif
