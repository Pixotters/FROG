#include "PhysicEngine.hpp"

#include <iostream> // delete

const float PhysicEngine::EARTH_GRAVITATION = 9.81f;


void PhysicEngine::update(GameObject * o, Physics * p)
{
  p->addVelocity( p->getAcceleration() );
  o->getTransform().move( p->getVelocity() );
}
