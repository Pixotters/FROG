#ifndef CTRL_JOYSTICKBUTTON_HPP
#define CTRL_JOYSTICKBUTTON_HPP

#include "Control/Button.hpp"

#include <SFML/Window/Event.hpp>


namespace ctrl{

  class Controller;

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
    bool occurred(Controller *);

  };

}

#endif
