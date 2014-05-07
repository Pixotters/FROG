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
    // TODO : this should not be check again ?
    auto bb1 = c.first->getComponent<Collider>("COLLIDER")->getBoundingBox();
    auto bb2 = c.second->getComponent<Collider>("COLLIDER")->getBoundingBox();
    if ( bb1.intersects(bb2) )
      script(c);
  }

}
