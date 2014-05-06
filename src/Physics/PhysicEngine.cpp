#include "FROG/Physics/PhysicEngine.hpp"

#include "FROG/Physics/Physics.hpp"

namespace frog{

  const float PhysicEngine::EARTH_GRAVITATION = 9.81f;


  void PhysicEngine::update(GameObject *)
  {
    /*    phi::Physics * p = o->getComponent<phi::Physics>();
    if(p != nullptr){
      // position
      p->addVelocity( p->getAcceleration() );
      o->transform.move( p->getVelocity() );
      // rotation
      p->addRotationForce( p->getRotationAcceleration() );
      o->transform.rotate( p->getRotationForce() );
      // scale
      p->addGrowth( p->getGrowthAcceleration() );
      o->transform.scale( p->getGrowth() );
    }
    */
  }

}
