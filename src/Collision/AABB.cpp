#include "FROG/Collision/AABB.hpp"
#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/EndPoint.hpp"

#include <iostream> // TODO remove

namespace frog{

  AABB::AABB(std::shared_ptr<Collider> c) : owner(c) 
  {
    min[0] = new EndPoint(this, c->getXMin(), true);
    min[1] = new EndPoint(this, c->getYMin(), true);
    max[0] = new EndPoint(this, c->getXMax(), false);
    max[1] = new EndPoint(this, c->getYMax(), false);
  }

  AABB::~AABB () 
  { 
    if (min[0] != nullptr)
      {
        delete min[0];
        min[0] = nullptr;
      }
    if (min[0] != nullptr)
      {
        delete min[1];
        min[1] = nullptr;
      }
    if (min[0] != nullptr)
      {
        delete max[0];
        max[0] = nullptr;
      }
    if (min[0] != nullptr)
      {
        delete max[1];
        max[1] = nullptr;
      }
  }

  void AABB::updateEPValues() 
  {
    std::cerr << "updating EP values " << std::endl;
    std::cerr << min[0]->value << " -> " << owner->getXMin() << std::endl \
              << min[1]->value << " -> " << owner->getYMin() << std::endl \
              << max[0]->value << " -> " << owner->getXMax() << std::endl \
              << max[1]->value << " -> " << owner->getYMax() << std::endl;
    min[0]->value = owner->getXMin();
    min[1]->value = owner->getYMin();
    max[0]->value = owner->getXMax();
    max[1]->value = owner->getYMax();
  }

}
