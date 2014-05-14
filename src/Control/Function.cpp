#include "FROG/Control/Function.hpp"

namespace frog{

  Function::Function(std::function<void()> f)
    : Command(), function(f)
  {
  }

  Function::~Function()
  {

  }

  void Function::execute()
  {
    function();
  }

  Function::PTR Function::create(std::function<void()> fun)
  {
    return PTR(new Function(fun) );
  }

}
  
