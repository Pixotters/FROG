#include "FROG/Collision/Collision.hpp"

namespace frog{

  Collision::Collision(GameObject * fst,
                       GameObject * snd,
                       Trigger tr)
    : first(fst), second(snd), trigger(tr)
  {
  }

  Collision::~Collision()
  {
  }

}
