#include "FROG/Collision/AABB.hpp"
#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/EndPoint.hpp"

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
    delete min[0];
    delete min[1];
    delete max[0];
    delete max[1];
  }

  void AABB::updateEPValues() 
  {
    min[0]->value = owner->getXMin();
    min[1]->value = owner->getYMin();
    max[0]->value = owner->getXMax();
    max[1]->value = owner->getYMax();
  }

}
