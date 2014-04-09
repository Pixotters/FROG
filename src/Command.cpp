#include "FROG/Command.hpp"

namespace frog{

  Command::Command()
  {

  }

  Command::~Command()
  {

  }

  bool Command::operator()()
  {
    execute();
  }

}
