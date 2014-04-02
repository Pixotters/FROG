#ifndef FROG_COMMAND_HPP
#define FROG_COMMAND_HPP

#include <string>

namespace frog{

  class Command
  {
    //// attributes ////
  protected:

    //// operations ////
  public:
    Command();
    virtual ~Command();
    virtual bool execute() = 0;
  };

}

#endif
