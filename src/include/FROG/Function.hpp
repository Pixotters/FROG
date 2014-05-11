#ifndef FROG_FUNCTION_HPP
#define FROG_FUNCTION_HPP

#include "FROG/Command.hpp"

#include <functional>
#include <memory>

namespace frog{

  class Function : virtual public Command
  {

  public:
    typedef std::shared_ptr<Function> PTR;

  protected:
    std::function<void()> function;

  public:
    Function(std::function<void()>);
    virtual ~Function();
    virtual void execute();
    static PTR create(std::function<void()>);
  };

}

#endif
