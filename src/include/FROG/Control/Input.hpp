#ifndef FROG_CTRL_INPUT_HPP
#define FROG_CTRL_INPUT_HPP

#include "FROG/Filter.hpp"

namespace frog{

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

}

#endif
