#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP

#include "AbstractController.hpp"
#include "Command.hpp"


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
    //    template <typename I, typename O>
    bool handle(AbstractController<Input,Command> *);
    virtual bool handle(Controller *);
  };

}

#endif
