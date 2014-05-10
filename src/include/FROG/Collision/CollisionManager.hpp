#ifndef FROG_COLLISION_MANAGER_HPP
#define FROG_COLLISION_MANAGER_HPP 1

/** Interface for collision managers */
#include "FROG/GameObject.hpp"

namespace frog{

  class CollisionManager  {

  public:

    CollisionManager(){};
  
    virtual ~CollisionManager() {}
  
    virtual void addObject(std::shared_ptr<GameObject>) = 0;
  
    virtual void updateObject(std::shared_ptr<GameObject>) = 0;
  
    virtual void removeObject(std::shared_ptr<GameObject>) = 0;

    virtual void update() = 0;
  
  };

}

#endif
