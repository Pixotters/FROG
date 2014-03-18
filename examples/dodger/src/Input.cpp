#include "Input/Input.hpp"

#include "Controller.hpp"
#include "Command.hpp"


namespace Input{

  Input::Input()
  {
  }

  Input::~Input()
  {
  }


  bool Input::handle(AbstractController<Input,Command> * ac) {
    Controller * c;
    if( (c = dynamic_cast<Controller*>(ac) ) ){
      return handle(c);
    }else{
      return false;
    }
  }


  bool Input::handle(Controller * c){
    return c->handle(this);
  }

}
