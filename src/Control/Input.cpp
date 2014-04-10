#include "FROG/Control/Input.hpp"

#include "FROG/Control/ControlHandler.hpp"

namespace frog{

  namespace ctrl{

    Input::Input()
    {
    }

    Input::~Input()
    {
    }


    bool Input::check(Filter<Input> * ac) {
      ControlHandler * c;
      if( (c = dynamic_cast<ControlHandler*>(ac) ) ){
        return check(c);
      }else{
        return false;
      }
    }


    bool Input::check(ControlHandler * c){
      return c->check(this);
    }

  }

}
