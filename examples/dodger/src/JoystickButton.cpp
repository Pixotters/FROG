#include "Input/JoystickButton.hpp"

namespace Input{


  JoystickButton::JoystickButton(const unsigned int& b, 
                                 const Button::Trigger& t)
    : Button(t), m_button(b) {

  }

  JoystickButton::~JoystickButton(){

  }

  unsigned int JoystickButton::getButton() const{
    return m_button;
  }

}
