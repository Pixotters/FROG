#ifndef CTRL_JOYSTICKSIMPLEBUTTON_HPP
#define CTRL_JOYSTICKSIMPLEBUTTON_HPP

#include "FROG/Control/JoystickButton.hpp"
#include "FROG/Control/SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

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
      bool check(ControlHandler *);

    };

  }

}

#endif
