#include "Input/JoystickButton.hpp"

namespace Input{


  JoystickButton::JoystickButton(const unsigned int& b, 
                                 const Button::Trigger& t,
                                 const unsigned int& i)
    : Button(t), m_button(b), m_id(i) {

  }

  JoystickButton::~JoystickButton(){

  }

  unsigned int JoystickButton::getButton() const{
    return m_button;
  }

  unsigned int JoystickButton::getID() const{
    return m_id;
  }

}
