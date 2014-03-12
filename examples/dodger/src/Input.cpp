#include "Input/Input.hpp"

#include "Controller.hpp"

namespace Input{

  Input::Input()
  {
  }

  Input::~Input()
  {
  }

  bool Input::handle(Controller * c)
  {
    return c->handle(this);
  }

}
