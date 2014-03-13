#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP

//#include "Controller.hpp"
class Controller;

namespace Input{

  class Input
  {
    //// attributes ////
  protected:

    //// operations ////
  public:
    Input();
    virtual ~Input();
    virtual bool handle(Controller * c) = 0;
  };

}

#endif
