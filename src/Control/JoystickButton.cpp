#include "Control/JoystickButton.hpp"
#include "Control/ControlHandler.hpp"

namespace frog{

  namespace ctrl{


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

    bool JoystickButton::check(ControlHandler * c)
    {
      return c->check(this);
    }


  }


}