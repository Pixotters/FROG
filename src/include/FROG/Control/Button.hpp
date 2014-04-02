#ifndef FROG_CTRL_BUTTON_HPP
#define FROG_CTRL_BUTTON_HPP

#include "FROG/Control/Input.hpp"

namespace frog{

  namespace ctrl{

    class Button : virtual public Input
    {
      //// operations ////
    public:
      Button();
      virtual ~Button();
    };

  }

}

#endif
