#include "PhysicEngine.hpp"

#include <iostream> // delete

void PhysicEngine::update(GameObject * o, Physics * p)
{
  p->addVelocity( p->getAcceleration() );
  o->getTransform().move( p->getVelocity() );
}
