#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>

class Action
{
  //// attributes ////
protected:
  std::string m_name;

  //// operations ////
public:
  Action();
  Action(const std::string&);
  virtual ~Action();
  std::string getName() const;
};

#endif
