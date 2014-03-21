#ifndef CTRL_JOYSTICKSIMPLEBUTTON_HPP
#define CTRL_JOYSTICKSIMPLEBUTTON_HPP

#include "Control/JoystickButton.hpp"
#include "Control/SimpleButton.hpp"
#include <SFML/Window/Event.hpp>


namespace ctrl{

class Controller;

  class JoystickSimpleButton : virtual public JoystickButton,
                               virtual public SimpleButton
  {

    //// attributes ////
  protected : 
    unsigned int m_button;
    unsigned int m_id;

    //// operations ////
  public:
    JoystickSimpleButton(const unsigned int&, 
                   const SimpleButton::Trigger& = SimpleButton::PRESSED,
                   const unsigned int& = 0);
    virtual ~JoystickSimpleButton();
    bool check(Controller *);

  };

}

#endif
