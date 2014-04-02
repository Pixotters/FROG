#ifndef CTRL_BUTTON_HPP
#define CTRL_BUTTON_HPP

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
