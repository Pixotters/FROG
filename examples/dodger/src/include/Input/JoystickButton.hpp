#ifndef INPUT_JOYSTICKBUTTON_HPP
#define INPUT_JOYSTICKBUTTON_HPP

#include "Button.hpp"

namespace Input{

class JoystickButton : virtual public Button
{

  //// attributes ////
protected : 
  unsigned int m_button;

  //// operations ////
public:
  JoystickButton(const unsigned int&, const Button::Trigger&);
  virtual ~JoystickButton();
  unsigned int getButton() const;
};

}
#endif
