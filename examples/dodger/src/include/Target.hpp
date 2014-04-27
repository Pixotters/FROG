#ifndef TARGET_HPP
#define TARGET_HPP

#include "Element.hpp"

using namespace frog;

class Target : virtual public Element
{

  //// attributes ////
protected:

  //// operations ////
public:
  Target(const AppInfo& appinfo);
  virtual ~Target();
};

#endif
