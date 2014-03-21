#ifndef CTRL_INPUT_HPP
#define CTRL_INPUT_HPP

#include "Filter.hpp"

namespace ctrl{

class ControlHandler;

  class Input
  {
    //// attributes ////
  protected:

    //// operations ////
  public:
    Input();
    virtual ~Input();
    //    template <typename I, typename O>
    bool check(Filter<Input> *);
    virtual bool check(ControlHandler *);
  };

}

#endif
