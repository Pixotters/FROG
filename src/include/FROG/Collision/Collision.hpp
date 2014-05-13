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
  
    std::shared_ptr <GameObject> first;
    std::shared_ptr <GameObject> second;
    Trigger trigger;

    Collision(std::shared_ptr <GameObject> fst,
              std::shared_ptr <GameObject> snd,
              Trigger = COLLISION);

    virtual ~Collision();
  };

}

#endif
