#ifndef FROG_COLLISIONMANAGER_HPP
#define FROG_COLLISIONMANAGER_HPP 1

/** Interface for collision managers */
#include "FROG/Core/GameObject.hpp"

namespace frog{

  class CollisionManager  {

  public:

    CollisionManager(){};
  
    virtual ~CollisionManager() {}
  
    virtual void addObject(const GameObject::PTR&) = 0;
    
    virtual void removeObject(const GameObject::PTR&) = 0;

    virtual void update() = 0;
  
  protected:
    virtual void updateObject(const GameObject::PTR&) = 0;

  };

}

#endif
