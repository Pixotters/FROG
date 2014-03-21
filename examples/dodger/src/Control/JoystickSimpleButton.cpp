#include "Control/JoystickSimpleButton.hpp"

#include "Control/Controller.hpp"

namespace ctrl{


  JoystickSimpleButton::JoystickSimpleButton(const unsigned int& b, 
                                             const SimpleButton::Trigger& t,
                                             const unsigned int& i)
    : JoystickButton(b,i), SimpleButton(t){

  }

  JoystickSimpleButton::~JoystickSimpleButton(){

  }

  bool JoystickSimpleButton::check(Controller * c)
  {
    return c->check(this);
  }


}
