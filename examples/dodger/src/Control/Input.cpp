#include "Control/Input.hpp"

#include "Control/Controller.hpp"
#include "Command.hpp"


namespace ctrl{

  Input::Input()
  {
  }

  Input::~Input()
  {
  }


  bool Input::occurred(AbstractController<Input,Command> * ac) {
    Controller * c;
    if( (c = dynamic_cast<Controller*>(ac) ) ){
      return occurred(c);
    }else{
      return false;
    }
  }


  bool Input::occurred(Controller * c){
    return c->occurred(this);
  }

}
