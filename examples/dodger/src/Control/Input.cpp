#include "Control/Input.hpp"

#include "Control/Controller.hpp"


namespace ctrl{

  Input::Input()
  {
  }

  Input::~Input()
  {
  }


  bool Input::check(AbstractController<Input> * ac) {
    Controller * c;
    if( (c = dynamic_cast<Controller*>(ac) ) ){
      return check(c);
    }else{
      return false;
    }
  }


  bool Input::check(Controller * c){
    return c->check(this);
  }

}
