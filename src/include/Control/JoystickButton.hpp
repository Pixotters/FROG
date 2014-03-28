#ifndef CTRL_JOYSTICKBUTTON_HPP
#define CTRL_JOYSTICKBUTTON_HPP

#include "Control/Button.hpp"

#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    class JoystickButton : virtual public Button
    {

      //// attributes ////
    protected : 
      unsigned int m_button;
      unsigned int m_id;

      //// operations ////
    public:
      JoystickButton(const unsigned int&, 
                     const unsigned int& = 0);
      virtual ~JoystickButton();
      unsigned int getButton() const;
      unsigned int getID() const;
      bool check(ControlHandler *);

    };

  }

}

#endif
