#ifndef INPUT_JOYSTICKBUTTON_HPP
#define INPUT_JOYSTICKBUTTON_HPP

#include "Button.hpp"

class Controller;

namespace Input{

class JoystickButton : virtual public Button
{

  //// attributes ////
protected : 
  unsigned int m_button;
  unsigned int m_id;

  //// operations ////
public:
  JoystickButton(const unsigned int&, 
                 const Button::Trigger& = Button::PRESSED,
                 const unsigned int& = 0);
  virtual ~JoystickButton();
  unsigned int getButton() const;
  unsigned int getID() const;
  bool handle(Controller *);

};

}
#endif
