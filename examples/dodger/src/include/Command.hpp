#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

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

#endif
