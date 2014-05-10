#ifndef FROG_FUNCTION_HPP
#define FROG_FUNCTION_HPP

#include "FROG/Command.hpp"

#include <functional>

namespace frog{

  class Function : virtual public Command
  {
  protected:
    std::function<void()> function;

  public:
    Function(std::function<void()>);
    virtual ~Function();
    virtual void execute();
  };

}

#endif
