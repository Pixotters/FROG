#include "FROG/Control/Command.hpp"

namespace frog{

  Command::Command()
  {

  }

  Command::~Command()
  {

  }

  void Command::operator()()
  {
    execute();
  }

  void Command::undo()
  {
  }

}
