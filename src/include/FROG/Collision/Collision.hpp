#ifndef FROG_COLLISION_HPP
#define FROG_COLLISION_HPP

#include "FROG/Core/GameObject.hpp"

namespace frog
{

  struct Collision
  {
    typedef enum
    {
      COLLISION,
      SEPARATION
    } Trigger;
  
    GameObject::PTR first;
    GameObject::PTR second;
    Trigger trigger;

    Collision(GameObject::PTR fst,
              GameObject::PTR snd,
              Trigger = COLLISION);

    virtual ~Collision();
  };

}

#endif
