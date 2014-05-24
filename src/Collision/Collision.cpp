#include "FROG/Collision/Collision.hpp"

namespace frog{

  Collision::Collision(GameObject::PTR fst,
                       GameObject::PTR snd,
                       Trigger tr)
    : first(fst), second(snd), trigger(tr)
  {
  }

  Collision::~Collision()
  {
  }

}
