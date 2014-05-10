#include "FROG/Function.hpp"

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

}
  
