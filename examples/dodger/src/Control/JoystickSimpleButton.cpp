#include "Control/JoystickSimpleButton.hpp"

#include "Control/ControlHandler.hpp"

namespace ctrl{


  JoystickSimpleButton::JoystickSimpleButton(const unsigned int& b, 
                                             const SimpleButton::Trigger& t,
                                             const unsigned int& i)
    : JoystickButton(b,i), SimpleButton(t){

  }

  JoystickSimpleButton::~JoystickSimpleButton(){

  }

  bool JoystickSimpleButton::check(ControlHandler * c)
  {
    return c->check(this);
  }


}
