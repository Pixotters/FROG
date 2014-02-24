#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include "GameObject.hpp"
#include "Physics.hpp"

class PhysicEngine{

  //// operations ////
public:
  static void update(GameObject *, Physics * p);

};

#endif
