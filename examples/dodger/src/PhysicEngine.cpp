#include "PhysicEngine.hpp"

#include <iostream> // delete

const float PhysicEngine::EARTH_GRAVITATION = 9.81f;


void PhysicEngine::update(GameObject * o, Physics * p)
{
  // position
  p->addVelocity( p->getAcceleration() );
  o->getTransform().move( p->getVelocity() );
  // rotation
  p->addRotationForce( p->getRotationAcceleration() );
  o->getTransform().rotate( p->getRotationForce() );
  // scale
  p->addGrowth( p->getGrowthAcceleration() );
  o->getTransform().scale( p->getGrowth() );
}
