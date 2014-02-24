#include "PhysicEngine.hpp"


void PhysicEngine::update(GameObject * o, Physics * p)
{
  p->addVelocity( p->getAcceleration() );
  o->getTransform().move( p->getVelocity() );
}
