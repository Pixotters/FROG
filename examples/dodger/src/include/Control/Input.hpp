#ifndef CTRL_INPUT_HPP
#define CTRL_INPUT_HPP

#include "Control/AbstractController.hpp"

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
    bool check(AbstractController<Input> *);
    virtual bool check(Controller *);
  };

}

#endif
