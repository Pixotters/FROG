#ifndef CTRL_INPUT_HPP
#define CTRL_INPUT_HPP

#include "Control/AbstractController.hpp"
#include "Command.hpp"

namespace ctrl{

class Controller;

  class Input
  {
    //// attributes ////
  protected:

    //// operations ////
  public:
    Input();
    virtual ~Input();
    //    template <typename I, typename O>
    bool occurred(AbstractController<Input,Command> *);
    virtual bool occurred(Controller *);
  };

}

#endif
