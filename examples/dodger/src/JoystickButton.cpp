#include "Input/JoystickButton.hpp"

#include "Controller.hpp"

namespace Input{


  JoystickButton::JoystickButton(const unsigned int& b, 
                                 const unsigned int& i)
    : Button(), m_button(b), m_id(i) {

  }

  JoystickButton::~JoystickButton(){

  }

  unsigned int JoystickButton::getButton() const{
    return m_button;
  }

  unsigned int JoystickButton::getID() const{
    return m_id;
  }

  bool JoystickButton::handle(Controller * c)
  {
    return c->handle(this);
  }


}
