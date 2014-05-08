#include "FROG/State.hpp"


namespace frog{

  State::State()
  {
  }

  State::~State()
  {
  }

  void State::loop()
  {
    update();
  }

}
