#include "FROG/Collision/Collider.hpp"

namespace frog{

  Collider::Collider(std::function<void(Collision)> fun)
    : Component()
  {
    script = fun;
  }

  Collider::~Collider()
  {

  }

  void Collider::setScript(std::function<void(Collision)> fun)
  {
    script = fun;
  }

  void Collider::onCollision(const Collision& c)
  {
    script(c);
  }

}
