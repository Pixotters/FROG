#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>

class Action
{
  //// attributes ////
protected:

  //// operations ////
public:
  Action();
  virtual ~Action();
  virtual bool execute() = 0;
};

#endif
