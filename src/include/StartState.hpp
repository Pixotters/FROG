#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "State.hpp"

#include "Control/ControlHandler.hpp"

#include <SFML/Graphics.hpp>

using namespace frog;

class StartState : virtual public State
{

  //// attributes ////
protected:

  //// operations ////
public:
  StartState();

  virtual ~StartState();

  virtual void update();

};


#endif
