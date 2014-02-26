#include "PhysicEngine.hpp"

#include <iostream> // delete

const float PhysicEngine::EARTH_GRAVITATION = 9.81f;


void PhysicEngine::update(GameObject * o, Physics * p)
{
  // position
  std::cout << "moving "<<std::endl;
  p->addVelocity( p->getAcceleration() );
  o->getTransform().move( p->getVelocity() );
  // rotation

  std::cout << "rotating "<< p->getRotationAcceleration() \
            << "->" << p->getRotationForce() \
            << "(" << o->getTransform().getRotation() <<")"<< std::endl;
  p->addRotationForce( p->getRotationAcceleration() );
  o->getTransform().rotate( p->getRotationForce() );
  // scale
  std::cout << "growing "<< p->getGrowthAcceleration().x \
            <<","<<p->getGrowthAcceleration().y \
            << "->" << p->getGrowth().x << "," << p->getGrowth().y  \
            << "(" << o->getTransform().getScale().x
            << "," << o->getTransform().getScale().y <<")"<< std::endl;
  p->addGrowth( p->getGrowthAcceleration() );
  o->getTransform().scale( p->getGrowth() );
}
