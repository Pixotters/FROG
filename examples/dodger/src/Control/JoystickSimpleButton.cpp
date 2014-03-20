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

  bool JoystickSimpleButton::occurred(Controller * c)
  {
    return c->occurred(this);
  }


}
