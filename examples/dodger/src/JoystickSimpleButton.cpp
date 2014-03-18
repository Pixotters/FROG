#include "Input/JoystickSimpleButton.hpp"

#include "Controller.hpp"

namespace Input{


  JoystickSimpleButton::JoystickSimpleButton(const unsigned int& b, 
                                             const SimpleButton::Trigger& t,
                                             const unsigned int& i)
    : JoystickButton(b,i), SimpleButton(t){

  }

  JoystickSimpleButton::~JoystickSimpleButton(){

  }

  bool JoystickSimpleButton::handle(Controller * c)
  {
    return c->handle(this);
  }


}
