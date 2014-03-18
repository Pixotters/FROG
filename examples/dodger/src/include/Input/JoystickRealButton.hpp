#ifndef INPUT_JOYSTICKREALBUTTON_HPP
#define INPUT_JOYSTICKREALBUTTON_HPP

#include "ContinuousButton.hpp"

class Controller;

namespace Input{

  class JoystickButton : virtual public ContinuousButton
  {

    //// attributes ////
  protected : 
    unsigned int m_button;
    unsigned int m_id;

    //// operations ////
  public:
    JoystickContinuousButton(const unsigned int&, 
                             const unsigned int& = 0);
    virtual ~JoystickContinuousButton();
    unsigned int getButton() const;
    unsigned int getID() const;
    bool handle(Controller *);
  };

}

#endif
