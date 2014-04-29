#ifndef FROG_CTRL_JOYSTICKBUTTON_HPP
#define FROG_CTRL_JOYSTICKBUTTON_HPP

#include "FROG/Control/Button.hpp"

#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    /*!
     * JoystickButton is a real-time button pressed on a joystick. 
     */
    class JoystickButton : virtual public Button
    {

      //// attributes ////
    protected : 
      unsigned int m_button;
      unsigned int m_id;

      //// operations ////
    public:
      JoystickButton(unsigned int, 
                     unsigned int = 0);
      virtual ~JoystickButton();
      unsigned int getButton() const;
      unsigned int getID() const;
      bool check(ControlHandler *);

    };

  }

}

#endif
