#include "FROG/Collision/Collision.hpp"

namespace frog{

  Collision::Collision(std::shared_ptr<GameObject> fst,
                       std::shared_ptr<GameObject> snd,
                       Trigger tr)
    : first(fst), second(snd), trigger(tr)
  {
  }

  Collision::~Collision()
  {
  }

}
