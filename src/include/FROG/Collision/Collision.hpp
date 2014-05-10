#ifndef FROG_COLLISION_HPP
#define FROG_COLLISION_HPP

#include "FROG/GameObject.hpp"

namespace frog{

struct Collision
{
  typedef enum
    {
      COLLISION,
      SEPARATION
    } Trigger;
  
  GameObject * first;
  GameObject * second;
  Trigger trigger;

  Collision(GameObject * fst,
            GameObject * snd,
            Trigger = COLLISION);
  virtual ~Collision();
  

};

}

#endif
