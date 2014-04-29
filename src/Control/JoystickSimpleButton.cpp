#include "FROG/Control/JoystickSimpleButton.hpp"

#include "FROG/Control/ControlHandler.hpp"

namespace frog{

  namespace ctrl{


    JoystickSimpleButton::JoystickSimpleButton(unsigned int b, 
                                               const SimpleButton::Trigger& t,
                                               unsigned int i)
      : JoystickButton(b,i), SimpleButton(t){

    }

    JoystickSimpleButton::~JoystickSimpleButton(){

    }

    bool JoystickSimpleButton::check(ControlHandler * c)
    {
      return c->check(this);
    }


  }

}
