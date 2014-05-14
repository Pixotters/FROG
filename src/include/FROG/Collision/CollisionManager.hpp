#ifndef FROG_COLLISION_MANAGER_HPP
#define FROG_COLLISION_MANAGER_HPP 1

/** Interface for collision managers */
#include "FROG/Core/GameObject.hpp"

namespace frog{

  class CollisionManager  {

  public:

    CollisionManager(){};
  
    virtual ~CollisionManager() {}
  
    virtual void addObject(GameObject::PTR) = 0;
  
    virtual void updateObject(GameObject::PTR) = 0;
  
    virtual void removeObject(GameObject::PTR) = 0;

    virtual void update() = 0;
  
  };

}

#endif
