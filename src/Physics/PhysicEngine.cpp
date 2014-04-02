#include "FROG/Physics/PhysicEngine.hpp"

#include "FROG/Physics/Physics.hpp"

namespace frog{

  const float PhysicEngine::EARTH_GRAVITATION = 9.81f;


  void PhysicEngine::update(GameObject * o)
  {
    phi::Physics * p = o->getComponent<phi::Physics>();
    if(p != nullptr){
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

  }

}
