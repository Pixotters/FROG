#ifndef INPUT_JOYSTICKSIMPLEBUTTON_HPP
#define INPUT_JOYSTICKSIMPLEBUTTON_HPP

#include "JoystickButton.hpp"
#include "SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

class Controller;

namespace Input{

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
    bool handle(Controller *);

  };

}

#endif
