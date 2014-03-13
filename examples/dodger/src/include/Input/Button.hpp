#ifndef INPUT_BUTTON_HPP
#define INPUT_BUTTON_HPP

#include "Input.hpp"

namespace Input{

  class Button : virtual public Input
  {
    //// operations ////
  public:
    Button();
    virtual ~Button();
  };

}


#endif
